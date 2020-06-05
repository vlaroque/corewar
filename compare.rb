turns = 20000;
nombre_derreurs = 0
nombre_derreurs_max = 10
'./corewar -dump '
file1 = ARGV[0]
file2 = ARGV[1]
file3 = ARGV[2]
file4 = ARGV[3]

#`./lasm #{file1.gsub(".cor", ".s")}`
debug = true

### compare strings and put in red differences and return first string
def string_compare(firstString, secondString)
	i = 0
	resultString = ""
	savedString= ""
	modified = false
	while firstString[i] && secondString[i] do
		
		if firstString[i] == "\n" then
			if modified == true then
				resultString = resultString + "\n" + savedString + "\n"
				modified = false
			else
				resultString = resultString + "\n"
			end
			savedString = ""
		end
		letter = firstString.slice(i)
		saved_letter = secondString.slice(i)
		if firstString[i] != secondString[i] then
			letter = "\e[31m" + letter + "\e[39m"
			saved_letter = "\e[32m" + saved_letter + "\e[39m"
			modified = true
		end
		if firstString[i] != "\n" then
			resultString.insert(-1, letter)
			savedString.insert(-1, saved_letter)
		end
		i += 1

	end
	return resultString
end

while turns < 50000 do
	puts turns
	res1 = `./corewar -dump #{turns.to_s} -n -1 #{file1} -n -2 #{file2} -n -3 #{file3} -n -4 #{file4}`
	res2 = `./lcorewar -d #{turns.to_s} #{file1} #{file2} #{file3} #{file4} 2> /dev/null`
	cut1 = res1.slice(res1.index("0x0000")..-1)
	cut2 = res2.slice(res2.index("0x0000")..-1)
	
	equal_strings = cut1.eql?(cut2)

	if !equal_strings && debug then
		print turns.to_s + " "
		puts equal_strings
		nombre_derreurs += 1
		#puts "mine\n" + cut1 + "real\n" + cut2
		puts string_compare(cut1, cut2)
		if nombre_derreurs == nombre_derreurs_max then
			exit
		end
	end
	turns = turns + 1
end
