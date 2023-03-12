#ifndef __LED_H__
#define __LED_H__

#define LED_R 0
#define LED_G 1
#define LED_B 2

#define IS_COLOR_VALID(COLOR) ( COLOR == LED_R || \
                                COLOR == LED_G || \
                                COLOR == LED_B  )


#endif