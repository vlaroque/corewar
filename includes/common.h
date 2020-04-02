#ifndef COMMON_H
# define COMMON_H

int		big_endian_int(void *ptr);
t_llu	read_bin_to_nbr(void *ptr, size_t len);
void	write_nbr_to_bin(t_llu nbr, void *dst, size_t len);

#endif
