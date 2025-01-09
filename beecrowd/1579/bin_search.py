def can_partition(arr, max_sum, c):
    current_sum = 0
    required_partitions = 1

    for num in arr:
        if current_sum + num > max_sum:
            required_partitions += 1
            current_sum = num
            if required_partitions > c:
                return False
        else:
            current_sum += num
    
    return True

def minimize_max_sum(arr, c):
    low = max(arr)
    high = sum(arr)
    
    while low < high:
        mid = (low + high) // 2
        if can_partition(arr, mid, c):
            high = mid
        else:
            low = mid + 1
            
    return low

n = int(input())
for _ in range(n):
    paineis, caminhoes, frete = map(int, input().split())
    pesos = [int(x) for x in input().split()]
    min_max_carga = minimize_max_sum(pesos, caminhoes)
    frete_total = min_max_carga * caminhoes * frete
    print(f'{min_max_carga} ${frete_total}')
