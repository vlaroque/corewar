.name           "42"
.comment        "ld load direct"

ld 12, r7
st r7, 64		#montre que le nombre a bien ete enregistre
ld %10, r2
ld %-10, r3
ld %2147483647, r4
ld %-2147483648, r5
ld %0, r6
ld -12, r7
st r2, 64		#montre que le nombre a bien ete enregistre
st r3, 64		#montre que le nombre a bien ete enregistre
st r4, 64		#montre que le nombre a bien ete enregistre
st r5, 64		#montre que le nombre a bien ete enregistre
st r6, 64		#montre que le nombre a bien ete enregistre
st r7, 64		#montre que le nombre a bien ete enregistre
