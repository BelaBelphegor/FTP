# FTP

# How server works

__________     Command      __________
| SERVER | ---------------> | CLIENT |
__________ <--------------  |________|
                 
				 =
________________     ________________              __________________________________
| Receiver read | => | Parse it into | == p(x) { 0 | Exit properly                   |}
| command.      |    | t_command.    |		   {1  | Search if an handler correspond |}
________________     _________________             ___________________________________
		-													     |
		|								 ___________________	 |
		|								 | Send appropriate |	 |
		__________________________       |	response.       | <__|
										 ____________________						
