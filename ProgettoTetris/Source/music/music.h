#ifndef MUSIC_H
#define MUSIC_H


//Default: 1.65
#define SPEEDUP 1.65

#define TIMERSCALER 1.1

#define SECOND 0x17D7840 * TIMERSCALER

#define FREQUENCY_SCALER 0.3

typedef char BOOL;
#define TRUE 1
#define FALSE 0

typedef enum note_durations
{
	time_semibiscroma = (unsigned int)(SECOND * SPEEDUP / 64.0f + 0.5), // 1/128
	time_biscroma = (unsigned int)(SECOND * SPEEDUP / 32.0f + 0.5), // 1/64
	time_semicroma = (unsigned int)(SECOND * SPEEDUP / 16.0f + 0.5), // 1/32
	time_croma = (unsigned int)(SECOND * SPEEDUP / 8.0f + 0.5), // 1/16
	time_semiminima = (unsigned int)(SECOND * SPEEDUP / 4.0f + 0.5), // 1/4
	time_minima = (unsigned int)(SECOND * SPEEDUP / 2.0f + 0.5), // 1/2
	time_semibreve = (unsigned int)(SECOND * SPEEDUP + 0.5), // 1
} NOTE_DURATION;

typedef enum frequencies
{
	a0b = 18969,	// 29Hz		k=18969 a0b
	b0 = 17747,	// 31Hz		k=17747 b0
	c1 = 16671,	// 33Hz		k=16671 c1
	d1b = 15889,	// 35Hz	k=15889 d1b
	d1 = 14997,	// 37Hz		k=14997 d1
	e1 = 13420,	// 41Hz		k=13420 e1
	f1 = 12503,	// 44Hz		k=12503 f1
	g1b = 11960,	// 46Hz		k=11960 gb1
	g1 = 11227,	// 49Hz		k=11227 g1
	a1b = 10579,	// 52Hz		k=10579 a1b
	a1 = 10003,	// 55Hz		k=10003 a1
	b1 = 8873,	// 62Hz		k=8873 b1
	c2 = 8414,	// 65Hz		k=8414 c2
	d2b = 7944,	// 69Hz		k=7944 d2b
	d2 = 7498,	// 73Hz		k=7498 d2
	e2 = 6711,	// 82Hz		k=6711 e2
	f2 = 6321,	// 87Hz		k=6321 f2
	g2b = 5980,	// 92Hz		k=5980 gb2
	g2 = 5614,	// 98Hz		k=5614 g2
	a2b = 5351,	// 104Hz	k=5351 a2b
	a2 = 5001,	// 110Hz	k=5001 a2
	b2 = 4500,	// 123Hz	k=4500 b2
	c3 = 4240,	// 131Hz	k=4240 c3
	d3b = 3972,	// 139Hz	k=3779 d3b
	d3 = 3779,	// 147Hz	k=3779 d3
	e3 = 3367,	// 165Hz	k=3367 e3
	f3 = 3175,	// 175Hz	k=3175 f3
	g3b = 2974,	// 185Hz	k=2974 gb3
	g3 = 2834,	// 196Hz	k=2834 g3
	a3b = 2670, // 208Hz  k=2670 a4b
	a3 = 2525,	// 220Hz	k=2525 a3
	b3 = 2249,	// 247Hz	k=2249 b3
	c4 = 2120,	// 262Hz	k=2120 c4
	d4b = 1986,	// 277Hz	k=1890 d4b
	d4 = 1890,	// 294Hz	k=1890 d4
	e4 = 1684,	// 330Hz	k=1684 e4
	f4 = 1592,	// 349Hz	k=1592 f4
	g4b = 1487,	// 370Hz	k=1487 g4b
	g4 = 1417,	// 392Hz	k=1417 g4
	a4 = 1263,	// 440Hz	k=1263 a4
	b4 = 1125,	// 494Hz	k=1125 b4
	c5 = 1062, 	// 523Hz	k=1062 c5
	nop = 0		// DO NOT SOUND
} FREQUENCY;


typedef struct 
{
	FREQUENCY freq;
	NOTE_DURATION duration;
} NOTE;

void playNote(NOTE note);
BOOL isNotePlaying(void);

#endif
/* EOF */
