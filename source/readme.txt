v1 release
v1.01 release2
v1.02 paladin fix

v1.1 - code rearranged/cleaned
	corsair custom mix added
	dps for different skills displayed concurrently
	clearer usage for elestaff with mages
	small bucc formula error fixed (no longer using lines to account for barrage bonus)
	no longer embarrassed by messy code, source released. now just embarrassed by poor coding practice
	
v2 SFML port
	jobinfo.txt rearranged
		weapon info added in to jobinfo
		mob count added to skills
		weapon stat multipliers hardcoded in, ive never seen a pserver change them
	cygnus knights added in
	made it much easier to add in more skills, you no longer need to change code and can stay in the jobinfo.txt
	classes can be added as well, no change in code required
		just make sure to follow the format
	while not desireable, ele staff multipliers have been hardcoded in the getMultMagic function
	
	

Notes :
-when a dev changes booster from +2 to +3, chain lightning speed is 630, paralyze&angelray is 690

~~~~~~~~
Todo : 
	-want to fix decimals in file reading		
	-need more info on combo attacks
	-want to add support for buff activation times, and taking that from DPS
	-want summon support
	-want multi-target support
	-want to add support for the damage cap
	-want head-to-head charts for all classes, including at different target numbers
	-want a GUI for setting gear stats, including ammo and shields
	-want support for accuracy calculations
	-want to add support for finding exp per hour, map density
	-maybe a GUI for setting mob distance and using attack range to get real scenario DPS comparisons
	-strafesnipe combo needs to be adjusted, its using decimals. You can't shoot 5.5 strafes between each snipe
	-might want to reimplement custom mix for corsair
~~~~~~~~
	

~~~~~~~~~~~~~~
Things that need testing :	
how bstep and bot interact, currently im assuming the first bot after bstep is a free cast, and finishes before bstep does
attack speed on bucc skills, currently using vanilla speeds
attack speed on Dark Impale (DrK), currently using crusher speeds
attack speed on all Cygnus skills, some unimplemented, nightwalker is using Night Lord speeds, using Vampire vanilla
ThunderBreaker combos, attack order etc
Heaven's hammer attack speed
	I believe it's close to 2520 at some speed, then Dream has an adjustment which makes it 450ms faster, close to 2070ms
Hero and Dawn Warrior Advanced Combo multiplier, currently assuming its 2.5 and 1.9 respectively
I doubt it does, but need confirmation if Cygnus final attack adds to 3rd or 4th job skills
	
~~~~~~~~~~~~~~


@~@~@~@~@~@~@~@~@
class IDs

bowmaster		0
marksman		1
windarcher		2
darkknight		3
hero			4
paladin			5
dawnwarrior		6
icelightning	7
firepoison		8
bishop			9
blazewizard		10
shadower		11
nightlord		12
nightwalker		13
buccaneer		14
corsair			15
thunderbreaker	16
@~@~@~@~@~@~@~@~@


~@~@~@~@~@~@~@~@~@~
job info layout

Name
mastery
critchance (before SE)
critdmg (before SE, default is 0)
other modifiers default value is 100 (elemental charges, shadow partner, combo, berserk etc)
	Paladin is ordered Holy Fire Lightning Ice
	currently multiplied by 100 to prevent decimals, meaning the default is 100

Attack1 percent1 lines1 mobcount1
speed[0][0], ....speed[0][4]...spamming speed = speed[0][5] if present
	this is looped until endof or combo is reading
combo
	loops reading a skill names until endof or combo is read
endof breaks all reading loops, ending the class reading


~@~@~@~@~@~@~@~@~@~

jobinfo.txt notes
	assassinate needs to be the first skill for Shadower, or darksight delay wont be implemented properly
		if assassinate is the first skill in a combo, darksight delay will be applied
		if its the second skill in a combo, darksight delay is not applied
	unfortunately, other class combos are a little more complicated and are hand coded. Only shad supports additional combos	