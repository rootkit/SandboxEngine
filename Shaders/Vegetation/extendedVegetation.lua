Script.shaderGrass=Shader:Load("Shaders/Vegetation/groundplants_extended.shader")
Script.shaderLeaves=Shader:Load("Shaders/Vegetation/leaves_extended.shader")
Script.radius=1 --float "Radius"
Script.season=0 --float "Season"
Script.seasonRate=0.1 --float "Season Change Rate"

function Script:Start()
	self.shaderGrass:SetFloat("playerRadius",self.radius)
end

function Script:UpdateWorld()
	self.shaderGrass:SetVec3("playerPos",self.entity:GetPosition(true))
end

function Script:UpdatePhysics()
	self.season=self.season+self.seasonRate*(Time:GetSpeed()/1000);
	self.shaderLeaves:SetFloat("playerSeason",self.season)
end