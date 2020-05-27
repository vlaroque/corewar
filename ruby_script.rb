turns = 0;
real_corewar = ""
'./corewar -dump '

while turns < 1000000 do
	res1 = `./corewar -dump #{turns.to_s} 43.cor`
	puts res1
	res2 = `./lcorewar -dump #{turns.to_s} 43.cor`
end

