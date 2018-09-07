local importer = 'local importer = require("importer").create(size)\n'
importer = 'local size=20\n'..importer
local memory = importer..'local memory = require "memory"\n'


return {
	id = "import",
	name = "Import 100K sequences of 20 bytes",
	repeats = 100000,
	--nocollect = true,
	--variables = { size = { min = 28, max = 44, step = 1 } },
	--variables = { size = { min = 15, max = 15*2^5, step = function (v) return 2*v end } },
	cases = {
		a_nothing   = {
			name = "data",
			nocollect = true,
			setup = importer,
			test = 'importer:skip()',
		},
		b_setref = {
			name = "setref",
			nocollect = true,
			setup = memory..'local m = memory.create()\n',
			test = 'assert(importer:setref(m))',
		},
		c_setmem = {
			name = "setmem",
			nocollect = true,
			setup = memory..'local m = memory.create(size)\n',
			test = 'assert(importer:setmem(m))',
		},
		d_newref = {
			name = "newref",
			setup = memory,
			test = 'assert(importer:newref())',
		},
		e_newmem = {
			name = "newmem",
			setup = memory,
			test = 'assert(importer:newmem())',
		},
		f_string = {
			name = "string",
			setup = importer,
			test = 'assert(importer:string())',
		},
	}
}
