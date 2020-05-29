.name           "42"
.comment        "ld load direct"

ld %67043585, r2 #03ff0101
ld %50331905, r4 #03000101
#ld %1879310352, r3 #70 04 00 10 pour la fin dun st avec bon enc_byte
ld %2130968592, r3 #7F 04 00 10 pour la fin dun st avec bon debut de encbyte mais la suite fausse
st r3, 6
st r2, 10
st r2, 20
