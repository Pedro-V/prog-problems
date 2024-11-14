from collections import deque

# TODO: fix WA on some larger inputs.

def unload(stack, queue, queue_cap, station):
    minutes = 0
    while stack and (stack[-1] == station + 1 or len(queue) < queue_cap):
        if stack[-1] == station + 1:
            stack.pop()
        else:
            queue.append(stack.pop())
        minutes += 1
    return minutes

def load(stack, queue, stack_cap):
    minutes = 0
    while queue and len(stack) < stack_cap:
        stack.append(queue.popleft())
        minutes += 1
    return minutes

def solve(stack, queues, stack_cap, queue_cap):
    num_stations = len(queues)
    station = 0
    minutes = 0
    while True:
        minutes += unload(stack, queues[station], queue_cap, station)
        minutes += load(stack, queues[station], stack_cap)
        if stack:
            station = (station + 1) % num_stations
            minutes += 2
        else:
            return minutes

def main():
    num_input_sets = int(input())
    for _ in range(num_input_sets):
        num_stations, stack_cap, queue_cap = map(int, input().split())
        queues = [deque() for _ in range(num_stations)]
        stack = []
        for i in range(num_stations):
            num_cargoes, *cargoes = map(int, input().split())
            queues[i] += cargoes
        minutes_taken = solve(stack, queues, stack_cap, queue_cap)
        print(minutes_taken)

if __name__ == '__main__':
    main()
