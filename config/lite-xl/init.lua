-- Minimal Config

local core = require "core"
local keymap = require "core.keymap"
-- local config = require "core.config"
-- local style = require "core.style"

------------------------------ CONFIG ----------------------------------------

core.reload_module("colors.onedark")
keymap.add { ["ctrl+q"] = "root:close"}
