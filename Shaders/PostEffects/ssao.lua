---------------------------------------------------------------------------
-- SSAO (Screen-Space Ambient Occlusion) by Igor Katrich 26/02/20015
-- Email: igorbgz@outlook.com
-- 
-- Update script file by Josh Klint and Shadmar 08/03/2015
---------------------------------------------------------------------------

function Script:Start()
        self.shader = Shader:Load("Shaders/PostEffects/SSAO/ssao.shader")
        self.combine = Shader:Load("Shaders/PostEffects/SSAO/ssao_combine.shader")
        self.noise = Texture:Load("Shaders/PostEffects/SSAO/noise.tex")--do this in start function
end

function Script:Render(camera,context,buffer,depth,diffuse,normals)

        --Check to see if buffer size has changed
        if self.buffer~=nil then
                if buffer:GetWidth()~=self.buffer:GetWidth() or buffer:GetHeight()~=self.buffer:GetHeight() then
                        self.buffer:Release()
                        self.buffer=nil
                end
        end

        if self.buffer==nil then
                self.buffer=Buffer:Create(buffer:GetWidth(),buffer:GetHeight())
                self.buffer:GetColorTexture():SetFilter(Texture.Smooth)
        end

        if self.shader 
        and self.combine
        and camera:GetScale().y==1 then 
                self.buffer:Enable()
                self.shader:Enable()     

                if self.noise~=nil then
                        self.noise:Bind(10)
                end

                depth:Bind(1)
                normals:Bind(2)
                context:DrawImage(diffuse,0,0,buffer:GetWidth(),buffer:GetHeight())

                buffer:Enable()
                diffuse:Bind(1) --Color
                self.buffer:GetColorTexture():Bind(2) --SSAO
                self.combine:Enable()
                context:DrawImage(diffuse,0,0,buffer:GetWidth(),buffer:GetHeight())
        end
end

function Script:Detach()
        --Release shaders
        if self.shader then
                self.shader:Release()
                self.shader = nil
        end
        if self.combine then
                self.combine:Release()
                self.combine = nil
        end
        --Release buffer
        if self.buffer~=nil then
                self.buffer:Release()
        end
        --Release noise texture
        if self.noise~=nil then
                self.noise:Release()
        end
end