local Swag = {}
Swag.__index = Swag

function Swag:new(swagmemorySize)
  local self = setmetatable({}, Swag)
  self.swagmemory = {}
  for i = 1, (swagmemorySize or 30000) do
    self.swagmemory[i] = 0
  end
  self.pointerggggg = 1
  return self
end

function Swag:executeStuff(code)
  local gregloop = {}
  local codeLength = #code

  for i = 1, codeLength do
    local instruction = string.sub(code, i, i)

    if instruction == '>' then
      self.pointerggggg = self.pointerggggg + 1
      if self.pointerggggg > #self.swagmemory then
        for j = #self.swagmemory + 1, #self.swagmemory * 2 do
          self.swagmemory[j] = 0
        end
      end
    elseif instruction == '<' then
      if self.pointerggggg > 1 then
        self.pointerggggg = self.pointerggggg - 1
      else
        io.stderr:write("error: pointer out of bounds\n")
        return
      end
    elseif instruction == '+' then
      self.swagmemory[self.pointerggggg] = (self.swagmemory[self.pointerggggg] + 1) % 256 
    elseif instruction == '-' then
      self.swagmemory[self.pointerggggg] = (self.swagmemory[self.pointerggggg] - 1 + 256) % 256
    elseif instruction == '.' then
      io.write(string.char(self.swagmemory[self.pointerggggg]))
    elseif instruction == ',' then
      local input = io.read(1)
      if input then
        self.swagmemory[self.pointerggggg] = string.byte(input)
      else
        self.swagmemory[self.pointerggggg] = 0
      end
    elseif instruction == '[' then
      if self.swagmemory[self.pointerggggg] == 0 then
        local nestL = 1
        local j = i
        while nestL > 0 and j < codeLength do
          j = j + 1
          local char = string.sub(code, j, j)
          if char == '[' then
            nestL = nestL + 1
          elseif char == ']' then
            nestL = nestL - 1
          end
        end
        if nestL > 0 then
          io.stderr:write("error: unmatched '['\n")
          return
        end
        i = j
      else
        table.insert(gregloop, i)
      end
    elseif instruction == ']' then
      if #gregloop == 0 then
        io.stderr:write("error: unmatched ']'\n")
        return
      end

      if self.swagmemory[self.pointerggggg] ~= 0 then
        i = table.remove(gregloop)
      else
        table.remove(gregloop)
      end
    end
  end

  if #gregloop > 0 then
    io.stderr:write("error: unmatched '['\n")
  end
end

function Swag:bracketgreg(code)
  local bracketthing = {}
  local codeLength = #code

  for i = 1, codeLength do
    local char = string.sub(code, i, i)
    if char == '[' then
      table.insert(bracketthing, i)
    elseif char == ']' then
      if #bracketthing == 0 then
        io.stderr:write(string.format("error: unmatched ']' at position %d\n", i))
        return false
      end
      table.remove(bracketthing)
    end
  end

  if #bracketthing > 0 then
    io.stderr:write(string.format("error: unmatched '[' at position %d\n", bracketthing[#bracketthing]))
    return false
  end

  return true
end

function Swag:fileexxxxxxxxx(filename)
  local file, err = io.open(filename, "r")
  if not file then
    io.stderr:write(string.format("error: could not open file %s\n", filename))
    return
  end
  local code = ""
  for line in file:lines() do
    for char in line:gmatch("[%><%+%-%.,%[%]]") do
      code = code .. char
    end
  end
  file:close()

  if self:bracketgreg(code) then
    self:executeStuff(code)
  end
end

local interpreter = Swag:new()

if #arg > 0 then
  interpreter:fileexxxxxxxxx(arg[1])
else
  io.write("enter brainfucm coddde (type 'end' to stop):\n")
  local code = ""
  while true do
    local line = io.read()
    if line == "end" then
      break
    end
    for char in line:gmatch("[%><%+%-%.,%[%]]") do
      code = code .. char
    end
  end

  io.write("\nrunning\n")
  if interpreter:bracketgreg(code) then
    local g = string.rep("=", 60)
    io.write(g .. "\n")
    interpreter:executeStuff(code)
  end
end

io.write("\npress enter to exit...")
io.read()
