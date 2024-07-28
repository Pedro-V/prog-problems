// Similar to brute_force.c, but instead of toggling only the i-th switch, we
// toggle half of the switches (except those whose doors have been found
// already), which helps cut the search space in half.

void set_a_switch(int door, int switch_positions[], int door_for_switch[], int n) {
  int i, result;
  int low = 0, high = n-1, mid;

  for (i = 0; i < n; i++)
    if (door_for_switch[i] == -1)
      switch_positions[i] = 0;

  result = tryCombination(switch_positions);
  if (result != door) {
    for (i = 0; i < n; i++)
      if (door_for_switch[i] == -1)
        switch_positions[i] = 1;
  }

  while (low != high) {
    mid = (low + high) / 2;

    // Toggle the first half of switches that aren't associated with a door yet.
    for (i = low; i <= mid; i++)
      if (door_for_switch[i] == -1)
        switch_positions[i] = 1 - switch_positions[i];

    result = tryCombination(switch_positions);

    if (result != door) { // The door was opened. Search on lower half.
      high = mid;

      // We need to close the door that was just opened, so that we can keep searching.
      for (i = low; i <= mid; i++)
        if (door_for_switch[i] == -1)
          switch_positions[i] = 1 - switch_positions[i];
    }
    else // The door is still closed. Search on upper half.
      low = mid + 1;
  }

  // After the search ends, we found the associated switch but 
  // the door is closed. We open it.
  door_for_switch[low] = door;
  switch_positions[low] = 1 - switch_positions[low];
}

void exploreCave(int n) {
  int switch_positions[n], door_for_switch[n];
  int i;

  for (i = 0; i < n; i++)
    door_for_switch[i] = -1;
  for (i = 0; i < n; i++)
    set_a_switch(i, switch_positions, door_for_switch, n);

  answer(switch_positions, door_for_switch);
}

