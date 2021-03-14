
local modname = ...
local M = {}
_G[modname] = M
package.loaded[modname] = M

local f = load("function test2() print(\"works\") end")
f()
M["test2"] = test2
_G["test2"] = nil


function M.test()
  print("This is a test")
end





