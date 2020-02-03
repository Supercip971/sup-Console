function ver()
  log ("help version 1", "null")
end
function info()
  log ("help is for get programm help","null")
end
function help()
  log ("help [command] for get the help of the command", "null")
end
function run()

   log ("help page \n", "null")
   log (" --- \n", "null")
   log ("programm -info | to get the programm info \n", "null")
   log ("programm -help | to get the programm help \n", "null")
   log ("programm -version | to get the programm version \n", "null")

   log (" --- \n", "null")
   log ("help | get global help \n", "null")
   log ("lua {code} | run lua code \n", "null")


end