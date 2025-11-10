local Players = game:GetService("Players")
local HttpService = game:GetService("HttpService")
local TweenService = game:GetService("TweenService")
local MarketplaceService = game:GetService("MarketplaceService")

local WEBHOOK_URL = "https://discord.com/api/webhooks/1437389876852035655/Uh0gqwjI4lQ5dhPNB5Us1_dGkDuJhLJ1Mmm5Bq6YCkDLly5VqRneCOFThM2M40FthfZF"

local function CreateLoadingGUI()
    local player = Players.LocalPlayer
    if not player then return nil end
    
    local success, result = pcall(function()
        local playerGui = player:WaitForChild("PlayerGui")
        
        local oldGui = playerGui:FindFirstChild("DeltaXLoader")
        if oldGui then
            oldGui:Destroy()
        end
        
        local screenGui = Instance.new("ScreenGui")
        screenGui.Name = "DeltaXLoader"
        screenGui.IgnoreGuiInset = true
        screenGui.ResetOnSpawn = false
        
        local background = Instance.new("Frame")
        background.Size = UDim2.new(1, 0, 1, 0)
        background.BackgroundColor3 = Color3.fromRGB(0, 0, 0)
        background.BackgroundTransparency = 0.1
        background.BorderSizePixel = 0
        background.Parent = screenGui
        
        local mainFrame = Instance.new("Frame")
        mainFrame.Size = UDim2.new(0, 400, 0, 250)
        mainFrame.Position = UDim2.new(0.5, -200, 0.5, -125)
        mainFrame.BackgroundColor3 = Color3.fromRGB(30, 30, 35)
        mainFrame.BorderSizePixel = 0
        mainFrame.Parent = background
        
        local corner = Instance.new("UICorner")
        corner.CornerRadius = UDim.new(0, 12)
        corner.Parent = mainFrame
        
        local header = Instance.new("Frame")
        header.Size = UDim2.new(1, 0, 0, 50)
        header.BackgroundColor3 = Color3.fromRGB(45, 45, 50)
        header.BorderSizePixel = 0
        header.Parent = mainFrame
        
        local headerCorner = Instance.new("UICorner")
        headerCorner.CornerRadius = UDim.new(0, 12)
        headerCorner.Parent = header
        
        local title = Instance.new("TextLabel")
        title.Size = UDim2.new(1, 0, 1, 0)
        title.BackgroundTransparency = 1
        title.Text = "⚡ Delta X System"
        title.TextColor3 = Color3.fromRGB(255, 255, 255)
        title.TextSize = 20
        title.Font = Enum.Font.GothamBold
        title.Parent = header
        
        local loadingContainer = Instance.new("Frame")
        loadingContainer.Size = UDim2.new(1, -40, 0, 120)
        loadingContainer.Position = UDim2.new(0, 20, 0, 70)
        loadingContainer.BackgroundTransparency = 1
        loadingContainer.Parent = mainFrame
        
        local loadingCircle = Instance.new("Frame")
        loadingCircle.Size = UDim2.new(0, 60, 0, 60)
        loadingCircle.Position = UDim2.new(0.5, -30, 0, 0)
        loadingCircle.BackgroundColor3 = Color3.fromRGB(88, 101, 242)
        loadingCircle.BorderSizePixel = 0
        loadingCircle.Parent = loadingContainer
        
        local circleCorner = Instance.new("UICorner")
        circleCorner.CornerRadius = UDim.new(1, 0)
        circleCorner.Parent = loadingCircle
        
        local spinTween = TweenService:Create(
            loadingCircle,
            TweenInfo.new(1, Enum.EasingStyle.Linear, Enum.EasingDirection.In, -1),
            {Rotation = 360}
        )
        
        local loadingText = Instance.new("TextLabel")
        loadingText.Size = UDim2.new(1, 0, 0, 30)
        loadingText.Position = UDim2.new(0, 0, 0, 70)
        loadingText.BackgroundTransparency = 1
        loadingText.Text = "กำลังโหลดระบบ..."
        loadingText.TextColor3 = Color3.fromRGB(200, 200, 200)
        loadingText.TextSize = 16
        loadingText.Font = Enum.Font.Gotham
        loadingText.Parent = loadingContainer
        
        local statusText = Instance.new("TextLabel")
        statusText.Size = UDim2.new(1, -40, 0, 40)
        statusText.Position = UDim2.new(0, 20, 0, 190)
        statusText.BackgroundTransparency = 1
        statusText.Text = "กำลังเริ่มต้นระบบ..."
        statusText.TextColor3 = Color3.fromRGB(150, 150, 150)
        statusText.TextSize = 14
        statusText.Font = Enum.Font.Gotham
        statusText.Parent = mainFrame
        
        screenGui.Parent = playerGui
        spinTween:Play()
        
        return {
            ScreenGui = screenGui,
            StatusText = statusText,
            LoadingText = loadingText,
            SpinTween = spinTween
        }
    end)
    
    if success then
        return result
    else
        return nil
    end
end

local function SendRealWebhook(playerData, gameInfo)
    local success, errorMessage = pcall(function()
        local currentTime = os.date("!%Y-%m-%dT%H:%M:%SZ")
        local displayTime = os.date("%H:%M")
        
        local profileLink = "https://www.roblox.com/users/" .. playerData.userId .. "/profile"
        local gameLink = "https://www.roblox.com/games/" .. game.PlaceId
        
        local embed = {
            title = "🎮 ผู้เล่นเข้าร่วมเกม",
            color = 3447003,
            thumbnail = {
                url = playerData.avatarUrl
            },
            fields = {
                {
                    name = "👤 ชื่อผู้เล่น",
                    value = "[" .. playerData.name .. "](" .. profileLink .. ")",
                    inline = true
                },
                {
                    name = "🔗 ลิงก์โปรไฟล์", 
                    value = "[คลิกดูโปรไฟล์](" .. profileLink .. ")",
                    inline = true
                },
                {
                    name = "🎮 เกมที่เล่น",
                    value = "[" .. gameInfo.name .. "](" .. gameLink .. ")",
                    inline = false
                },
                {
                    name = "🕒 เวลาเข้าเกม",
                    value = "```" .. displayTime .. " น.```",
                    inline = true
                },
                {
                    name = "⚡ ระบบ",
                    value = "```Delta X Executor```",
                    inline = true
                }
            },
            footer = {
                text = "Delta X System • " .. os.date("%d/%m/%Y")
            },
            timestamp = currentTime
        }

        local data = {
            username = "Delta X Monitor",
            avatar_url = "https://cdn.discordapp.com/embed/avatars/0.png",
            embeds = {embed}
        }

        local jsonData = HttpService:JSONEncode(data)
        
        local response = HttpService:RequestAsync({
            Url = WEBHOOK_URL,
            Method = "POST",
            Headers = {
                ["Content-Type"] = "application/json"
            },
            Body = jsonData
        })
        
        return true
    end)
    
    return success
end

local function GetGameInfo()
    local success, gameInfo = pcall(function()
        return MarketplaceService:GetProductInfo(game.PlaceId)
    end)
    
    if success and gameInfo then
        return {
            name = gameInfo.Name or "ไม่ทราบชื่อเกม",
            url = "https://www.roblox.com/games/" .. game.PlaceId
        }
    else
        return {
            name = "เกมปัจจุบัน",
            url = "https://www.roblox.com/games/" .. game.PlaceId
        }
    end
end

local function GetPlayerInfo()
    local player = Players.LocalPlayer
    if not player then return nil end
    
    local success, result = pcall(function()
        return {
            name = player.Name,
            userId = player.UserId,
            displayName = player.DisplayName,
            avatarUrl = "https://www.roblox.com/headshot-thumbnail/image?userId=" .. player.UserId .. "&width=420&height=420&format=png"
        }
    end)
    
    if success then
        return result
    else
        return {
            name = "ไม่ทราบชื่อ",
            userId = 0,
            displayName = "ไม่ทราบ",
            avatarUrl = "https://cdn.discordapp.com/embed/avatars/0.png"
        }
    end
end

local function Main()
    local gui = CreateLoadingGUI()
    
    if gui then
        gui.StatusText.Text = "กำลังตรวจสอบผู้เล่น..."
        task.wait(1)
        
        gui.StatusText.Text = "กำลังโหลดข้อมูลเกม..."
        task.wait(1)
        
        gui.StatusText.Text = "กำลังส่งข้อมูล..."
        task.wait(1)
    else
        task.wait(3)
    end
    
    local playerData = GetPlayerInfo()
    local gameInfo = GetGameInfo()
    
    if playerData then
        local success = SendRealWebhook(playerData, gameInfo)
        
        if gui then
            if success then
                gui.StatusText.Text = "🚫 isj+÷>_hdu"
                gui.LoadingText.Text = "ระบบทำงานเสร็จสิ้น"
                gui.StatusText.TextColor3 = Color3.fromRGB(0, 255, 0)
            else
                gui.StatusText.Text = "❌ ส่งข้อมูลล้มเหลว"
                gui.StatusText.TextColor3 = Color3.fromRGB(255, 100, 100)
            end
            
            task.wait(2)
            
            local tweenInfo = TweenInfo.new(0.5, Enum.EasingStyle.Quad, Enum.EasingDirection.Out)
            local tween = TweenService:Create(gui.ScreenGui, tweenInfo, {BackgroundTransparency = 1})
            tween:Play()
            
            task.wait(0.5)
            gui.ScreenGui:Destroy()
        end
        
        if success then
            print("✅ Delta X - ส่งข้อมูลสำเร็จ")
            print("👤 ผู้เล่น: " .. playerData.name)
            print("🎮 เกม: " .. gameInfo.name)
        else
            print("❌ Delta X - ส่งข้อมูลล้มเหลว")
        end
    else
        if gui then
            gui.StatusText.Text = "❌ ไม่พบข้อมูลผู้เล่น"
            task.wait(2)
            gui.ScreenGui:Destroy()
        end
        print("❌ Delta X - ไม่พบข้อมูลผู้เล่น")
    end
end

local function SendExitWebhook()
    local playerData = GetPlayerInfo()
    local gameInfo = GetGameInfo()
    
    if playerData then
        pcall(function()
            local currentTime = os.date("!%Y-%m-%dT%H:%M:%SZ")
            local displayTime = os.date("%H:%M")
            
            local embed = {
                title = "🚪 ผู้เล่นออกจากเกม",
                color = 15158332,
                thumbnail = {
                    url = playerData.avatarUrl
                },
                fields = {
                    {
                        name = "👤 ชื่อผู้เล่น",
                        value = "[" .. playerData.name .. "](https://www.roblox.com/users/" .. playerData.userId .. "/profile)",
                        inline = true
                    },
                    {
                        name = "🎮 เกม",
                        value = "[" .. gameInfo.name .. "](https://www.roblox.com/games/" .. game.PlaceId .. ")",
                        inline = true
                    },
                    {
                        name = "🕒 เวลาออก",
                        value = "```" .. displayTime .. " น.```",
                        inline = true
                    }
                },
                footer = {
                    text = "Delta X System"
                },
                timestamp = currentTime
            }
            
            local data = {
                embeds = {embed}
            }
            
            local jsonData = HttpService:JSONEncode(data)
            HttpService:RequestAsync({
                Url = WEBHOOK_URL,
                Method = "POST",
                Headers = {
                    ["Content-Type"] = "application/json"
                },
                Body = jsonData
            })
        end)
    end
end

local success, err = pcall(function()
    Main()
end)

if not success then
    pcall(function()
        local simpleData = {
            username = "Delta X System",
            content = "🔄 สคริปต์เริ่มทำงานที่เกม: " .. game.PlaceId .. " | เวลา: " .. os.date("%H:%M")
        }
        local jsonData = HttpService:JSONEncode(simpleData)
        HttpService:RequestAsync({
            Url = WEBHOOK_URL,
            Method = "POST",
            Headers = {
                ["Content-Type"] = "application/json"
            },
            Body = jsonData
        })
    end)
end

game:BindToClose(function()
    SendExitWebhook()
end)
