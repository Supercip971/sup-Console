function ver()
  log ("info World", "error")
end
function info()
  log ("info World", "warning")
end
function help()
  log ("info World", "")
end
function run(arg1, arg2, arg3)
	if arg1 == nil then
	   
		 log ("arg1 is nil \n", "")
	else
		log (arg1, "")
	end    
	     
	     if arg2 == nil then
	   
		 log ("arg2 is nil \n", "")

	else
		log (arg2, "")
	end    
	if arg3 == nil then
	   
		 log ("arg3 is nil \n", "")

	else
		log (arg3, "")
	end          
end