Script.atached = false -- bool "Atached"
Script.atachedJoint = NULL -- Entity "Atached Entity"
Script.jointSide = 0 -- choice "Joint Side" "Front, Right, Back, Left"

function Script:Start()

    self.parentModel = self.entity:GetParent()

    self:UpdateJoints();
end

function Script:UpdateJoints()
    if self.jointSide == 0 then

        System:Print("Joint Founded")

        System:Print(self.fixed)

        if self.fixed == true then

            System:Print("Entity Fixed")

            if self.atached == true then

                System:Print("Entity Atached")

                local atachedParent = self.atachedJoint.entity:GetParent()

                local position = atachedParent:GetPosition(true);

                self.parentModel:SetPosition(position.x,position.y, position.z,true)

            end
            --local position = parent:GetPosition();

			--System:Print(position)

            --self.entity:SetPosition(position.x,position.y, position.z,true)
        end
    end
end

function Script:UpdateWorld()
    --self.parentModel = self.entity:GetParent()
    --self:UpdateJoints();
end
