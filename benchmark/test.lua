local importer = require("importer").create(4)
local memory = require "memory"

local ref = memory.create()
local mem = memory.create(4)

math.randomseed(os.time())

for i=1, 4^4 do
	print(i, importer:newref(ref):get(1, -1))
end
