def can_partition(arr, max_sum, c):
    current_sum = 0
    required_partitions = 1
    i = 0

    while i < len(arr):
        if current_sum + arr[i] > max_sum:
            required_partitions += 1
            if required_partitions > c:
                return False
            current_sum = 0
        else:
            current_sum += arr[i]
            i += 1
    
    return True

def minimize_max_sum(arr, c):
    low = 0
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
