--[[
Style	Meaning
BUTTON_PUSH	Standard push button.
BUTTON_CHECKBOX	A check box button that displays a tick when it's state is True.
BUTTON_RADIO	A radio button is accompanied by a small circular indicator, filled when it's state is True.
BUTTON_OK	Standard push button that is also activated when the user presses the RETURN key.
BUTTON_CANCEL	Standard push button that is also activated when the user presses the ESCAPE key.
]]

Script.pushed=false
Script.hovered=false
Script.radius=0

function Script:Draw(x,y,width,height)
	--System:Print("Paint Button")
	local gui = self.widget:GetGUI()
	local pos = self.widget:GetPosition(true)
	local sz = self.widget:GetSize(true)
	
	gui:SetColor(1,1,1,1)

	if self.pushed then
		gui:SetColor(0.2,0.2,0.2)
	else
		if self.hovered then
			gui:SetColor(0.3,0.3,0.3)
		else
			gui:SetColor(0.25,0.25,0.25)
		end
	end
	gui:DrawRect(pos.x,pos.y,sz.width,sz.height,0,self.radius)
	
	if self.pushed then
		gui:SetColor(0.0,0.0,0.0)
	else
		gui:SetColor(0.75,0.75,0.75)
	end
	gui:DrawLine(pos.x,pos.y,pos.x+sz.width,pos.y)
	gui:DrawLine(pos.x,pos.y,pos.x,pos.y+sz.height)
	
	if self.pushed then
		gui:SetColor(0.75,0.75,0.75)
	else
		gui:SetColor(0.0,0.0,0.0)		
	end
	gui:DrawLine(pos.x+1,pos.y+sz.height-1,pos.x+sz.width-1,pos.y+sz.height-1)
	gui:DrawLine(pos.x+sz.width-1,pos.y+1,pos.x+sz.width-1,pos.y+sz.height)
	
	gui:SetColor(0.75,0.75,0.75)
	
	local text = self.widget:GetText()
	if text~="" then
		if self.pushed then
			gui:DrawText(text,pos.x+1,pos.y+1,sz.width,sz.height,Text.Center+Text.VCenter)	
		else
			gui:DrawText(text,pos.x,pos.y,sz.width,sz.height,Text.Center+Text.VCenter)	
		end
	end
	
	gui:SetColor(Math:Random(0,1),Math:Random(0,1),Math:Random(0,1))
	--gui:DrawRect(0,0,1000,1000)
	
	--gui:DrawRect(pos.x,pos.y,self.widget.size.width,self.widget.size.height,1,3)
end

function Script:MouseEnter(x,y)
	self.hovered = true
	self.widget:Redraw()
end

function Script:MouseLeave(x,y)
	self.hovered = false
	self.widget:Redraw()
end

function Script:MouseMove(x,y)
	--System:Print("MouseMove")
end

function Script:MouseDown(button,x,y)
	--System:Print("MouseDown")
	self.pushed=true
	self.widget:Redraw()
end

function Script:MouseUp(button,x,y)
	--System:Print("MouseUp")
	local gui = self.widget:GetGUI()
	self.pushed=false
	if self.hovered then
		EventQueue:Emit(Event.WidgetAction,self.widget)
	end
	self.widget:Redraw()
end

function Script:KeyDown(button,x,y)
	--System:Print("KeyDown")
end

function Script:KeyUp(button,x,y)
	--System:Print("KeyUp")	
end
