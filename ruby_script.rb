turns = 0;
nombre_derreurs = 0
real_corewar = ""
'./corewar -dump '
file1 = ARGV[0]

`./lasm #{file1.gsub(".cor", ".s")}`
debug = true

while turns < 10000 do
	res1 = `./corewar -dump #{turns.to_s} -n -1 #{file1}`
	res2 = `./lcorewar -d #{turns.to_s} #{file1}`
	cut1 = res1.slice(res1.index("0x0000")..-1)
	cut2 = res2.slice(res2.index("0x0000")..-1)
	
	print turns.to_s + " "
	equal_strings = cut1.eql?(cut2)

	puts equal_strings
	if !equal_strings && debug then
		nombre_derreurs += 1
		puts "mine\n" + cut1 + "real\n" + cut2
		if nombre_derreurs == 2 then
			exit
		end
	end
	turns = turns + 1
end
