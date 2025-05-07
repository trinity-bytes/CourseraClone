#pragma once
template <typename Pred>

int busquedaBinaria(int l, int r, Pred pred) 
{
	int m = l + (r - l) / 2;

	if (l > r) return -1;
	if (l == r) return l;
	
	if (pred(m)) return busquedaBinaria(l, m - 1, pred);
	return busquedaBinaria(m + 1, r, pred);
}
