-----------------------------
-- Godrays + bloom shader
-----------------------------

--Called once at start
function Script:Start()
	--Load this script's shader
	self.shader = Shader:Load("Shaders/PostEffects/00_shaders/_bloom.shader")
	self.shader_hblur = Shader:Load("Shaders/PostEffects/00_shaders/_hblur.shader")
	self.shader_vblur = Shader:Load("Shaders/PostEffects/00_shaders/_vblur.shader")
	self.shader_bright = Shader:Load("Shaders/PostEffects/00_shaders/_brightpass.shader")
	self.shader_pass = Shader:Load("Shaders/PostEffects/00_shaders/_passthrough.shader")
	--GodRays
	self.shader_god = Shader:Load("Shaders/PostEffects/00_shaders/_godray.shader")
	self.shader_uw  = Shader:Load("Shaders/PostEffects/00_shaders/_underwater.shader")
end

--Called each time the camera is rendered
function Script:Render(camera,context,buffer,depth,diffuse,normals)

	if self.lightsource==nil then
		self.world=World:GetCurrent()
		for i=self.world:CountEntities()-1,0,-1 do
			if self.world:GetEntity(i):GetClass()==Object.DirectionalLightClass then
				  self.lightsource=self.world:GetEntity(i)
				  tolua.cast(self.lightsource,"DirectionalLight")
				  break
			end
		end
	end
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

		self.buftex3 = Texture:Create(buffer:GetWidth(),buffer:GetHeight(),Texture.RGB, 0, 1, 0)
		self.buftex3:SetFilter(Texture.Smooth)
		self.buftex3:SetClampMode(true,true)

		self.buftex4 = Texture:Create(buffer:GetWidth()/4,buffer:GetHeight()/4,Texture.RGB, 0, 1, 0)
		self.buftex4:SetFilter(Texture.Smooth)
		self.buftex4:SetClampMode(true,true)
		
		self.buffer={}
		self.buffer[0]=Buffer:Create(buffer:GetWidth(),buffer:GetHeight())
		self.buffer[0]:SetColorTexture(self.buftex)

		self.buffer[1]=Buffer:Create(w/2,h/2,1,0)
		self.buffer[1]:SetColorTexture(self.buftex1)

		self.buffer[2]=Buffer:Create(w/4,h/4,1,0)
		self.buffer[2]:SetColorTexture(self.buftex2)

		self.buffer[3]=Buffer:Create(buffer:GetWidth(),buffer:GetHeight())
		self.buffer[3]:SetColorTexture(self.buftex3)

		self.buffer[4]=Buffer:Create(w/4,h/4,1,0)
		self.buffer[4]:SetColorTexture(self.buftex4)
	end
	
	if (
		self.shader_bright 
		and self.shader_vblur 
		and self.shader_hblur
		and self.shader
		and self.shader_god
		and self.shader_pass
		and self.shader_uw
		and camera:GetScale().y==1
		) then
		--Save for bloom pass
		buffer:Disable()

		--Brightpass
		self.buffer[0]:Enable()
		self.shader_bright:Enable()

		--adjusts for bloom
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

		--adjusts for godrays
		local fExposure=camera:GetKeyValue("godray_fExposure","0.3")
		local fDecay=   camera:GetKeyValue("godray_fDecay","0.97")
		local fDensity= camera:GetKeyValue("godray_fDensity","0.6")
		local fWeight=  camera:GetKeyValue("godray_fWeight","0.44")
		local fClamp=   camera:GetKeyValue("godray_fClamp","1.0")
		local fWhiteOnly=camera:GetKeyValue("godray_fWhiteOnly","0")
		local getsunpos=camera:GetKeyValue("godray_pos","0.1,0.1,0.1")

		if self.lightsource~=nil then 
			self.dir=Vec3(-self.lightsource.mat.k.x,-self.lightsource.mat.k.y,-self.lightsource.mat.k.z):Normalize()
		else
			self.dir=Vec3(getsunpos):Normalize()
		end
		
		self.shader_god:SetVec3("sunDir",self.dir)
		self.camdir = Vec3(camera.mat.k.x,camera.mat.k.y,camera.mat.k.z):Normalize()
		self.shader_god:SetVec3("camDir",self.camdir)

		self.dir=Vec3(self.dir.x*1e8,self.dir.y*1e8,self.dir.z*1e8)
		self.pos = camera:Project(self.dir)
		self.pos = Vec3(self.pos.x,self.pos.y,self.pos.z)
		if self.shader_uw then self.shader_uw:SetVec3("shaftpos",self.pos) end
		
		self.buffer[4]:Enable()
		self.shader_god:Enable()  
		self.shader_god:SetVec2("screenLightPos",Vec2(self.pos.x/buffer:GetWidth(),self.pos.y/buffer:GetHeight()))
		self.shader_god:SetFloat("fExposure",fExposure)
		self.shader_god:SetFloat("fDecay",fDecay)
		self.shader_god:SetFloat("fDensity",fDensity)
		self.shader_god:SetFloat("fWeight",fWeight)
		self.shader_god:SetFloat("fClamp",fClamp)
		self.shader_god:SetInt("fWhiteOnly",fWhiteOnly)
		self.buffer[2]:GetColorTexture():Bind(1)
		context:DrawImage(self.buffer[2]:GetColorTexture(),0,0,buffer:GetWidth(),buffer:GetHeight())
		self.buffer[4]:Disable() 

		--hblur
		self.buffer[2]:Enable()
		self.shader_hblur:Enable()  
		self.buffer[4]:GetColorTexture():Bind(1)
		context:DrawImage(self.buffer[4]:GetColorTexture(),0,0,buffer:GetWidth(),buffer:GetHeight())
		self.buffer[2]:Disable()

		--vblur
		self.buffer[4]:Enable()
		self.shader_vblur:Enable()
		self.buffer[2]:GetColorTexture():Bind(1)
		context:DrawImage(self.buffer[2]:GetColorTexture(),0,0,buffer:GetWidth(),buffer:GetHeight()) 
		self.buffer[4]:Disable()

		--bloom
		buffer:Enable()
		self.shader:Enable()
		diffuse:Bind(1)
		tex=self.buffer[4]:GetColorTexture()
		tex:Bind(2)
		context:DrawImage(self.buffer[4]:GetColorTexture(),0,0,buffer:GetWidth(),buffer:GetHeight()) 
	else
		buffer:Enable()
		if self.shader_pass then self.shader_pass:Enable() end
		context:DrawRect(0,0,buffer:GetWidth(),buffer:GetHeight())
	end
end

--Called when the effect is detached or the camera is deleted
function Script:Detach()
	if self.cam then
		self.cam:SetKeyValue("hdr_expose","1.25")
		self.cam:SetKeyValue("hdr_clampiris","0.0,2.0")
	end
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
	if self.shader_god then
		self.shader_god:Release()
		self.shader_god = nil
	end
	if self.shader_uw then
		self.shader_uw:Release()
		self.shader_uw = nil
	end
	if self.shader_pass then
		self.shader_pass:Release()
		self.shader_pass = nil
	end
	--Release buffers
	if self.buffer~=nil then
		self.buffer[0]:Release()
		self.buffer[1]:Release()
		self.buffer[2]:Release()
		self.buffer[3]:Release()
		self.buffer[4]:Release()
		self.buffer=nil
	end		
end