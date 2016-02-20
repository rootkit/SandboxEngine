--------------------------------------------
-- Bloom Shader by Shadmar, with brightpass
--------------------------------------------

--Called once at start
function Script:Start()
	--Load this script's shader
	self.shader = Shader:Load("Shaders/PostEffects/00_shaders/_bloom.shader")
	self.shader_hblur = Shader:Load("Shaders/PostEffects/00_shaders/_hblur.shader")
	self.shader_vblur = Shader:Load("Shaders/PostEffects/00_shaders/_vblur.shader")
	self.shader_bright = Shader:Load("Shaders/PostEffects/00_shaders/_brightpass.shader")
	self.shader_pass = Shader:Load("Shaders/PostEffects/00_shaders/_passthrough.shader")
end

--Called each time the camera is rendered
function Script:Render(camera,context,buffer,depth,diffuse,normals)
	self.cam=camera
	
	--Create downsample buffers if they don't exist
	if self.buffer==nil then
		local w=buffer:GetWidth()
		local h=buffer:GetHeight()

		self.buftex = Texture:Create(buffer:GetWidth(),buffer:GetHeight(),Texture.RGB, 0, 1, 0)
		self.buftex:SetFilter(Texture.Smooth)
		self.buftex:SetClampMode(true,true)

		self.buftex1 = Texture:Create(buffer:GetWidth()/2,buffer:GetHeight()/2,Texture.RGB, 0, 1, 0)
		self.buftex1:SetFilter(Texture.Smooth)
		self.buftex1:SetClampMode(true,true)

		self.buftex2 = Texture:Create(buffer:GetWidth()/4,buffer:GetHeight()/4,Texture.RGB, 0, 1, 0)
		self.buftex2:SetFilter(Texture.Smooth)
		self.buftex2:SetClampMode(true,true)
		
		self.buffer={}
		self.buffer[0]=Buffer:Create(buffer:GetWidth(),buffer:GetHeight())
		self.buffer[0]:SetColorTexture(self.buftex)

		self.buffer[1]=Buffer:Create(w/2,h/2,1,0)
		self.buffer[1]:SetColorTexture(self.buftex1)

		self.buffer[2]=Buffer:Create(w/4,h/4,1,0)
		self.buffer[2]:SetColorTexture(self.buftex2)		
	end
	
	--Save for bloom pass
	buffer:Disable()

	
	--Brightpass
	if (
		self.shader_bright 
		and self.shader_vblur 
		and self.shader_hblur
		and self.shader
		and self.shader_pass
		and camera:GetScale().y==1
		) then
		self.buffer[0]:Enable()
		self.shader_bright:Enable()

		-- adjust bloom highpass filter
		local Luminance=camera:GetKeyValue("bloom_Luminance","0.1")
		local fMiddleGray=camera:GetKeyValue("bloom_MiddleGray","0.48")
		local fWhiteCutoff=camera:GetKeyValue("bloom_WhiteCutoff","0.98")
		
		--adjust hdr since bloom is used
		camera:SetKeyValue("hdr_expose","0.7")
		camera:SetKeyValue("hdr_clampiris","0.8,2.0")

		self.shader_bright:SetFloat("Luminance",Luminance)
		self.shader_bright:SetFloat("fMiddleGray",fMiddleGray)
		self.shader_bright:SetFloat("fWhiteCutoff",fWhiteCutoff)
		diffuse:Bind(1)
		context:DrawImage(diffuse,0,0,buffer:GetWidth(),buffer:GetHeight())
		self.buffer[0]:Disable()

		--Downsample
		self.buffer[0]:Blit(self.buffer[1],Buffer.Color)
		self.buffer[1]:Blit(self.buffer[2],Buffer.Color)

		--hblur
		self.buffer[0]:Enable()
		self.shader_hblur:Enable()  
		self.buffer[2]:GetColorTexture():Bind(1)
		context:DrawImage(self.buffer[2]:GetColorTexture(),0,0,buffer:GetWidth(),buffer:GetHeight())
		self.buffer[0]:Disable()

		--vblur
		self.buffer[1]:Enable()
		self.shader_vblur:Enable()
		self.buffer[0]:GetColorTexture():Bind(1)
		context:DrawImage(self.buffer[0]:GetColorTexture(),0,0,buffer:GetWidth(),buffer:GetHeight()) 
		self.buffer[1]:Disable()

		--bloom
		buffer:Enable()
		self.shader:Enable()
		diffuse:Bind(1)
		tex=self.buffer[1]:GetColorTexture()
		tex:Bind(2)
		context:DrawImage(self.buffer[1]:GetColorTexture(),0,0,buffer:GetWidth(),buffer:GetHeight())
	else
		buffer:Enable()
		if self.shader_pass then self.shader_pass:Enable() end
		context:DrawRect(0,0,buffer:GetWidth(),buffer:GetHeight())
	end
end

--Called when the effect is detached or the camera is deleted
function Script:Detach()
	if self.shader then
		self.shader:Release()
		self.shader = nil
	end
	if self.shader_vblur then
		self.shader_vblur:Release()
		self.shader_vblur = nil
	end
	if self.shader_hblur then
		self.shader_hblur:Release()
		self.shader_hblur = nil
	end
	if self.shader_bright then
		self.shader_bright:Release()
		self.shader_bright = nil
	end
	--Release buffers
	if self.buffer~=nil then
		self.buffer[0]:Release()
		self.buffer[1]:Release()
		self.buffer[2]:Release()
		self.buffer=nil
	end
	--Reset HDR
	if self.cam then
		self.cam:SetKeyValue("hdr_expose","1.25")
		self.cam:SetKeyValue("hdr_clampiris","0.0,2.0")
	end
end