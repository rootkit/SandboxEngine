Script.ObjectType = "" --string
Script.RightHandBone = nil --entity

function Script:Start()

	--self.entity:SetGravityMode(false)
	--local shape = Shape:Box(0,0,0, 0,0,0, 1,1,1)
	--self.entity:SetShape(shape)
	self.entity:SetMass(10)
	self.entity:SetCollisionType(Collision.Debris)
	self.entity:SetParent(nil)
end

function Script:UpdateWorld()

	self.entity:SetPosition(self.RightHandBone:GetPosition(true).x,
										self.RightHandBone:GetPosition(true).y,
										self.RightHandBone:GetPosition(true).z,true)

	self.entity:SetRotation(self.RightHandBone:GetRotation(true).x,
										self.RightHandBone:GetRotation(true).y,
										self.RightHandBone:GetRotation(true).z,true)
	--self.entity:SetRotation(self.RightHandBone:GetRotation(false),false)

end

function Script:Collision(entity,position,normal,speed)
	--entity:Hide()
end