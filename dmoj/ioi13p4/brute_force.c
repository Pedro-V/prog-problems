//

// This sets the correct switch for the given door in the door_for_switch array.
void set_a_switch(int door, int switch_positions[], int door_for_switch[], int n) {
  int found, i, result;

  // Turn off all switches whose door is unknown.
  for (i = 0; i < n; i++)
    if (door_for_switch[i] == -1)
      switch_positions[i] = 0;

  // If door isn't closed, make it closed by
  // turning on all switches whose door is unknown.
  result = tryCombination(switch_positions);
  if (result != door) {
    for (i = 0; i < n; i++)
      if (door_for_switch[i] == -1)
        switch_positions[i] = 1;
  }

  i = 0;
  found = 0;
  while (!found) {
    if (door_for_switch[i] == -1) {
      // Toggle the i-th switch, and check if this opens the door.
      // If it does, we found this door's switch.
      switch_positions[i] = 1 - switch_positions[i];
      result = tryCombination(switch_positions);
      if (result != door)
        found = 1;
      else
        i++;
    }
    else
      i++;
  }

  // i must be the switch associated with our door.
  door_for_switch[i] = door;
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
