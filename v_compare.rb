verbosity = ARGV[0]
file1 = ARGV[1]
file2 = ARGV[2]
file3 = ARGV[3]
file4 = ARGV[4]

end_turn = 13700
end_cmd_m = ""
end_cmd_r = ""

if end_turn != 0 then
	end_cmd_m = "-dump #{end_turn.to_s}"
	end_cmd_r = "-d #{end_turn.to_s}"
end


res1 = `./corewar -v #{verbosity} -n -1 #{file1} -n -2 #{file2} -n -3 #{file3} -n -4 #{file4} #{end_cmd_m}`
puts "my corewar generated"
res2 = `./ressources/vm-champ-linux/corewar -v #{verbosity} #{file1} #{file2} #{file3} #{file4} #{end_cmd_r} 2> /dev/null`
puts "real corewar generated"

array_mine = res1.slice(res1.index("It is")..-1)
array_mine = array_mine.split("It is now cycle ")
array_real = res2.slice(res2.index("It is")..-1)
array_real = array_real.split("It is now cycle ")

puts "arrays generated"
 
turn = 0
errors = 10
while turn < 30000 and array_mine[turn] and array_real[turn] do
	if array_mine[turn] != array_real[turn] then
		puts "mine " + array_mine[turn] + "real " + array_real[turn] + "\n"
		errors -= 1
		if errors == 0
			exit
		end
	end
	turn += 1
end
