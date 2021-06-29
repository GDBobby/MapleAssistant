v1 release
v1.01 release2
v1.02 had to fix paladin

v1.1 - code rearranged/cleaned
	corsair custom mix added
	dps for different skills displayed concurrently
	clearer usage for elestaff with mages
	small bucc formula error fixed (no longer using lines to account for barrage bonus)
	
	
	

Notes :
-when a dev changes booster from +2 to +3, chain lightning speed is 630, paralyze&angelray is 690
-Pierce is also Piercing Arrow?

~~~~~~~~
Todo : 
	-want to fix decimals in file reading		
	-need more info on combo attacks
	
	v2
	-want to add support for buff activation times, and taking that from DPS
	-want summon support
	-want multi-target support
	-want to add support for the damage cap
	
	v3
	-want head-to-head charts for all classes, including at different target numbers
	-want a GUI for setting gear stats
	
	v4
	-want support for accuracy calculations
	-want to add support for finding exp per hour, map density
	-maybe a GUI for setting mob distance and using attack range to pull DPS from real scenarios
	
	-need a workaround for using std::strings to initialize list boxes, benched for now
~~~~~~~~
	

~~~~~~~~~~~~~~
Things that need testing :
-actual delay for ass/bstep, barrage + demo, barrage + dragonstrike, dragonstrike + snatch, its currently jerry rigged
-charge advantage/disadvantage for paladin
	according to ayumilove its like this at max level
		holy 			1.5 ~ .5
		(sword)ice 		1.5 ~ .5
		(sword)fire		1.5 ~ .5
		(sword)lightn	1.5 ~ .5
		(mace)inferno 	1.25 ~ .75
		(mace)blizzard	1.25 ~ .75
		(mace)lightning/divine isn't mentioned, but maybe its also 1.25,.75
	i dont have any personal experience with maces being so weak, but maybe i missed it	
	
-pierce testing, need to know full charged attack time
	ayumilove says it takes 1 second to charge, is it 1sec + attack speed per attack? or can it start recharging without delay
	for now im rolling with no delay on recharge, 1 fully charged piercing arrow per second
-according to ayumilove darksight delay is 240ms, but in my experience its 60. Using 240 for now, but want further testing	
	
~~~~~~~~~~~~~~


@~@~@~@~@~@~@~@~@
class IDs

bowmaster 	0
marksman 	1
darkknight	2
hero		3
paladin		4
i/l			5
f/p			6
bishop		7
shadower	8
nightlord	9
bucc		10
corsair		11
@~@~@~@~@~@~@~@~@


@~@~@~@~@~@~@~@~@
weapon IDs

0 bow
1 xbow
2 spear
3 1hsword
4 2hsword
5 1ham
6 2ham (2h axe/mace)
7 elestaff
8 dagger
9 claw
10 knuckle
11 gun
@~@~@~@~@~@~@~@~@


~@~@~@~@~@~@~@~@~@~
weapon info layout

weapon multiplier (multipled by 10 cause no decimal)

(skill 1, speed 2) (skill 2, speed 2)
...
(singletarget skill 1, speed 6) (st2, sp6) (mt1, sp6) (multitarget 2, speed 6)
(if applicable, the next row is the spamming speed, i.e. boomerang step)
~@~@~@~@~@~@~@~@~@~


~@~@~@~@~@~@~@~@~@~
job info layout

Name
mastery
Attack1 Attack2(skill names) --- (if you add/remove skills, update the skill structs)
percent1 percent2
lines1 lines2
critchance (before SE)
critdmg (before SE, default is 0)
other modifiers default value is 1 (elemental charges, shadow partner, combo, berserk etc)
	include elemental staff and elemental amplification
	Paladin is ordered Holy Fire Lightning Ice
	currently multiplied by 100 to prevent decimals, default is 100
~@~@~@~@~@~@~@~@~@~