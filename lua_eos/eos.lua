
-- http://lua-users.org/wiki/LuaStyleGuide

function _eos_delay(t)
  local x = 0
  local y = 0
  while (x < 100000) do
    x = x + 1
    while (y < t * 50000) do
      y = y + 1
    end
  end
end

-- comment out the following line for eos
eos_delay = _eos_delay

schd = {}
local tasks = {}

local function scheduler()
  while(1) do
    for k,v in pairs(tasks) do
      success, args = coroutine.resume(v.co)
      if success == false then
        print("Error: " .. args)
        return
      end
      eos_delay(1000)
    end
  end
end

local YIELD = 1
local WAIT_DELAY = 2
local WAIT_EVENT = 3

function schd.create_task(task_func)
  local e = {}
  e["co"] = coroutine.create(task_func)
  e["state"] = YIELD
  e["subscription"] = {}
  e["ev_q"] = {}
  table.insert(tasks, e)
end

function schd.scheduler()
  scheduler()
end

function schd.yield()
  coroutine.yield()
end



function task1( t )
  local x = 10
  while(1) do
    print("task1, x = " .. x)
    x=x+1
    schd.yield()
  end
end

function task2( t )
  local y = 1
  while(1) do
    print("task2, y = " .. y)
    y=y+1
    schd.yield()
  end
end

schd.create_task(task1)
schd.create_task(task2)
schd.scheduler()




