function Script:Start()
	--Load this script's shader
	self.shader = Shader:Load("Shaders/PostEffects/00_shaders/_lensflare.shader")
	self.shader_pass = Shader:Load("Shaders/PostEffects/00_shaders/_passthrough.shader")
end

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
	
	--water present at all?
	if self.world:GetWaterMode()==true then height=self.world:GetWaterHeight()
	else height=0 end
	
	if self.shader
	and self.shader_pass
	and camera:GetScale().y==1
	and camera:GetPosition().y > height
	then
		self.shader:Enable()
		depth:Bind(3)
		
		if self.lightsource~=nil then 
			self.dir=Vec3(-self.lightsource.mat.k.x,-self.lightsource.mat.k.y,-self.lightsource.mat.k.z):Normalize()
		else
			self.dir=Vec3(getsunpos):Normalize()
		end
	
		self.dir=Vec3(self.dir.x*1e8,self.dir.y*1e8,self.dir.z*1e8)
		self.pos = camera:Project(self.dir)
		self.shader:SetVec2("screenLightPos",Vec2(self.pos.x/buffer:GetWidth(),self.pos.y/buffer:GetHeight()))
		context:DrawImage(diffuse,0,0,buffer:GetWidth(),buffer:GetHeight())
	else
		buffer:Enable()
		if self.shader_pass then self.shader_pass:Enable() end
		context:DrawRect(0,0,buffer:GetWidth(),buffer:GetHeight())
	end
end