def summarize_consumption(arr):
    output_arr = []
    consump, people = arr[0]
    sum_consump = consump
    sum_people = people
    last_consump = consump

    for i in range(1, len(arr)):
        consump, people = arr[i]
        if last_consump == consump:
            sum_consump += consump
            sum_people += people
        else:
            output_arr.append((last_consump, sum_people))
            sum_consump = consump
            sum_people = people
            last_consump = consump

    output_arr.append((last_consump, sum_people))
    sum_consump = consump
    sum_people = people

    return output_arr

def main():
    case_num = 0
    while True:
        n = int(input())
        if n == 0:
            return
        case_num += 1
        if case_num != 1:
            print()

        total_people = 0
        total_consump = 0
        arr = []
        for _ in range(n):
            people, consump = map(int, input().split())
            total_people += people
            total_consump += consump
            x = (consump // people, people)
            arr.append(x)
        arr.sort()
        summary = summarize_consumption(arr)
        output = ' '.join(map(lambda t: f'{t[1]}-{t[0]}', summary))

        print(f'Cidade# {case_num}:')
        print(output)
        avg = total_consump / total_people
        avg = int(avg * 100) / 100
        print(f'Consumo medio: {avg:.2f} m3.')

if __name__ == '__main__':
    main()
