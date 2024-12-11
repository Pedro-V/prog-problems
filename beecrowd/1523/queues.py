# Idea: Use a deque for simulating the parking lot,
# and a priority queue to model the time cars go out of it.

from collections import deque
from heapq import *


def usable_parking_lot(timings, capacity):
    dq = deque(maxlen=capacity)
    h = []

    for t_in, t_out in timings:
        # Cars going out before we go in.
        while h and h[0] <= t_in:
            if h[0] != dq[0]:
                return False
            dq.popleft()
            heappop(h)
        # More cars than we can park.
        if len(dq) == capacity:
            return False

        heappush(h, t_out)
        dq.appendleft(t_out)

    while dq:
        if h[0] != dq[0]:
            return False
        dq.popleft()
        heappop(h)

    return True


def main():
    while True:
        num_cars, capacity = map(int, input().split())
        if num_cars == 0:
            return

        timings = []
        for _ in range(num_cars):
            t_in, t_out = map(int, input().split())
            timings.append((t_in, t_out))

        print("Sim" if usable_parking_lot(timings, capacity) else "Nao")


if __name__ == "__main__":
    main()
