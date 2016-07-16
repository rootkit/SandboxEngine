--[[
Style	Meaning
PANEL_BORDER	Panel is drawn with a border.
PANEL_ACTIVE	Panel generates mouse move events.
PANEL_GROUP	Panel is drawn with a titled etched border.
]]--

Script.borderindent=8

function Script:MouseMove(x,y)
	System:Print(x..", "..y)
end

function Script:Start()
	if self.widget:GetStyle()==1 then
	--if bit32.band(style,1) then
	--	self.widget:SetPadding(self.borderindent,self.borderindent,self.borderindent,self.borderindent)
	end
end

function Script:Draw(x,y,width,height)
	System:Print("Paint Panel")
	local gui = self.widget:GetGUI()
	local pos = self.widget:GetPosition(true)
	local sz = self.widget:GetSize(true)
	
	gui:SetColor(0.25,0.25,0.25,1)
	gui:DrawRect(pos.x,pos.y,sz.width,sz.height)
	gui:SetColor(0.5,0.5,0.5,1)
	
	self.borderindent = 8 * gui:GetScale()
	
	if self.widget:GetStyle()==1 then
	--	gui:DrawRect(pos.x+self.borderindent-2,pos.y+self.borderindent-2,sz.width-self.borderindent*2+4,sz.height-self.borderindent*2+4,1)
	end
	
	local text = self.widget:GetText()
	if text~="" then
		
	end
	
end
