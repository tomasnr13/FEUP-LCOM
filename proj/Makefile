PROG=proj

SRCS = main.c Keyboard.c graphic.c GAme.c Sprite.c spaceship.c enemies.c mouse.c Menu.c rtc.c

# __LCOM_OPTIMIZED__ disables most of the LCF's overhead (and functionality!)
CPPFLAGS += -pedantic -D __LCOM_OPTIMIZED__

DPADD += ${LIBLCF}
LDADD += -llcf

.include <minix.lcom.mk>
