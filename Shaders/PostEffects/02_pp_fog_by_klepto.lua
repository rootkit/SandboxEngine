--------------------------------------------------------
-- Fog Shader by Klepto2, some modifications by Shadmar
--------------------------------------------------------

--Called once at start
function Script:Start()
	self.shader = Shader:Load("Shaders/PostEffects/00_shaders/_klepto_fog.shader")
	self.shader_pass = Shader:Load("Shaders/PostEffects/00_shaders/_passthrough.shader")
	self.world=World:GetCurrent()
end

--Called each time the camera is rendered
function Script:Render(camera,context,buffer,depth,diffuse,normals)
	--Enable the shader and draw the diffuse image onscreen
	
	--water present at all?
	if self.world:GetWaterMode()==true 
	then 
		height=self.world:GetWaterHeight()
	else 
		height=0 
	end
	
	if (
		self.shader
		and self.shader_pass
		and camera:GetScale().y==1
		) then
		
		self.shader:Enable() 
		depth:Bind(3)
		
		--adjust fog ranges
		local fogrange=camera:GetKeyValue("fog_fogrange","0,200")
		local fogcolor=camera:GetKeyValue("fog_fogcolor","0.57,0.53,0.55,1.0")
		local fogangle=camera:GetKeyValue("fog_fogangle","5,21")
		local fogislocal=camera:GetKeyValue("fog_fogislocal","0")

		self.shader:SetVec2("fogrange",Vec2(fogrange))
		self.shader:SetVec4("fogcolor",Vec4(fogcolor))
		self.shader:SetVec2("fogangle",Vec2(fogangle))
		self.shader:SetInt("fogislocal",fogislocal)
		self.shader:SetFloat("waterisactive",camera:GetScale().y)
		self.shader:SetFloat("waterheight",height)
	else
		buffer:Enable()
		if self.shader_pass then self.shader_pass:Enable() end
		context:DrawRect(0,0,buffer:GetWidth(),buffer:GetHeight())
	end

	context:DrawImage(diffuse,0,0,buffer:GetWidth(),buffer:GetHeight())
end

--Called when the effect is detached or the camera is deleted
function Script:Detach()
	if self.shader then
		self.shader:Release()
		self.shader = nil
	end
	if self.shader_pass then
		self.shader_pass:Release()
		self.shader_pass = nil
	end
end