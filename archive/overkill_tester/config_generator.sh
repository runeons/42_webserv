
#!/usr/bin/env zsh

# usage server_count location_mode server_attribut_mode

server_count > [0-9]
location_mode
	> default: [/]
	> t1: [/] + [dir1]
	> t2: [/] + [dir1] + [dir2]
	> t3: [/] + [dir1] + [dir1/dir1.1] + [dir2]
	> t4: [/] + [dir1] + [dir1/dir1.1] + [dir1/dir1.1/dir1.1.1] + [dir2]
error
	> default: [404] + [500]
server_attribut_mode
	> default: host + port + server_name + root + max_client_body