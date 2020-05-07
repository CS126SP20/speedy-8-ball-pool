# Development

---
- **4/18/2020** Drew table, ball, and cue images.
  - Still need to place balls in correct position (in triangle with cue ball separate)
  - Place cue in correct starting position
  - No movement yet
  
- **4/19/2020** The cue is "rotating" but not in the correct way.
  - need to fix rotation so that it rotates around ball and not some arbitrary point
  
- **4/21/2020** The balls are now moving when hit by cue, but the cue force, angle, and position is not determined by user.
  - need to make borders so that balls are not flying off the screen
  - need to set contact listener so cue stops after hitting the balls
  
- **4/25/2020** Added borders to keep balls on the table
  - need to fix the mass of the balls, they are moving as if there is no gravity
  
- **4/26/2020** Changed cue so that is stops moving once hit ball by setting contact listener
  - need to set rotating ability by mouse tracking
  - need to added power bar so speed is adjustable
  
- **4/27/2020** Added pockets so that the balls disappear when they are hit in.
  - need to fix the positioning a bit because it is still inaccurate
  - need to get the cue rotating, still not working properly and by user clicking

- **4/28/2020** Added friction and mass to balls so they move more realistically and added rotation of cue
  - need to start implementing game logic
  
- **4/29/2020** Added rotation of cue through mouse tracking
  - need to include power bar so that speed is controlled by user
  
- **5/1/2020** Added placing of cue ball it is hit in
  - still need to add power bar

- **5/2/2020** Added power bar
  - power of cue is now controlled by user through up and down keys
  - still need to add some game logic

- **5/3/2020** Added time display to show how long it takes to win and added SQL library
  - still need to add database usage
  
- **5/4/2020** Added user input of username and start screen
  - still need to added end screen with database implementation
 
- **5/5/2020** Added database implementation to display current user best scores and all user best scores
  - still need to added tests
  
- **5/6/2020** Removed hardcoded numbers and strings and made them constants and wrote tests
  - Future improvements: Make the two player version of solid vs stripes with all the rules, added line extended from cue to help with aiming
