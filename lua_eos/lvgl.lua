
local modname = ...
local M = {}
_G[modname] = M
package.loaded[modname] = M

--setfenv(1,M)

function M.test()
  print("This is a test")
end


--module(...)


function test2()
  print("This is test 2")
end




