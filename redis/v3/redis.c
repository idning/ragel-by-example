
#line 1 "redis.rl"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

typedef char   *sds;

struct sdshdr {
    int             len;
    int             free;
    char            buf[];
};

sds
sdsnewlen(const void *init, size_t initlen)
{
    struct sdshdr  *sh;

    sh = malloc(sizeof(struct sdshdr) + initlen + 1);
    if (sh == NULL)
        return NULL;
    sh->len = initlen;
    sh->free = 0;
    if (initlen && init)
        memcpy(sh->buf, init, initlen);
    sh->buf[initlen] = '\0';
    return (char *)sh->buf;
}

typedef struct Msg {
    int             argc;       // if argc < 0, means this msg is not used
    char          **argv;
} Msg;

Msg            *
msg_new(int argc)
{
    Msg            *msg;
    msg = malloc(sizeof(Msg));
    msg->argc = argc;
    msg->argv = malloc(sizeof(char *) * msg->argc);
    return msg;
}

#line 100 "redis.rl"

#line 51 "redis.c"
static const char _redis_actions[] = {
    0, 1, 0, 1, 1, 1, 2, 1,
    3, 1, 4, 1, 5, 1, 6, 1,
    7
};

static const char _redis_cond_offsets[] = {
    0, 0, 0, 0, 0, 0, 1, 2,
    4, 5, 6, 7, 8
};

static const char _redis_cond_lengths[] = {
    0, 0, 0, 0, 0, 1, 1, 2,
    1, 1, 1, 1, 1
};

static const short _redis_cond_keys[] = {
    36, 36, 48, 57, 48, 57, 60, 60,
    62, 62, -128, 127, -128, 127, 62, 62,
    36, 36, 0
};

static const char _redis_cond_spaces[] = {
    0, 0, 0, 0, 0, 2, 2, 0,
    0, 0
};

static const char _redis_key_offsets[] = {
    0, 0, 1, 3, 6, 7, 8, 10,
    13, 14, 16, 19, 20
};

static const short _redis_trans_keys[] = {
    42, 48, 57, 60, 48, 57, 62, 1060,
    1072, 1081, 1084, 1072, 1081, 1086, 1920, 2175,
    1596, 1920, 2175, 1086, 1060, 0
};

static const char _redis_single_lengths[] = {
    0, 1, 0, 1, 1, 1, 0, 1,
    1, 0, 1, 1, 1
};

static const char _redis_range_lengths[] = {
    0, 0, 1, 1, 0, 0, 1, 1,
    0, 1, 1, 0, 0
};

static const char _redis_index_offsets[] = {
    0, 0, 2, 4, 7, 9, 11, 13,
    16, 18, 20, 23, 25
};

static const char _redis_trans_targs[] = {
    2, 0, 3, 0, 4, 3, 0, 5,
    0, 6, 0, 7, 0, 8, 7, 0,
    9, 0, 10, 0, 11, 10, 0, 12,
    0, 6, 0, 0
};

static const char _redis_trans_actions[] = {
    1, 0, 5, 0, 7, 0, 0, 0,
    0, 0, 0, 9, 0, 11, 0, 0,
    0, 0, 13, 0, 15, 0, 0, 0,
    0, 0, 0, 0
};

static const char _redis_eof_actions[] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 3
};

static const int redis_start = 1;
static const int redis_first_final = 12;
static const int redis_error = 0;

static const int redis_en_main = 1;

#line 103 "redis.rl"

Msg            *
msg_parse(uint8_t * buf, uint32_t buflen)
{
    int             cs;         //used by ragel
    uint8_t        *p, *pe, *eof;   //used by ragel

    Msg            *msg = NULL;
    uint8_t        *last;       //last pos
    uint32_t        argc;
    uint32_t        arglen;
    uint32_t        len, c_arg = 0;

    p = buf;
    eof = pe = buf + buflen;

#line 147 "redis.c"
    {
        cs = redis_start;
    }

#line 152 "redis.c"
    {
        int             _klen;
        unsigned int    _trans;
        short           _widec;
        const char     *_acts;
        unsigned int    _nacts;
        const short    *_keys;

        if (p == pe)
            goto _test_eof;
        if (cs == 0)
            goto _out;
      _resume:
        _widec = (*p);
        _klen = _redis_cond_lengths[cs];
        _keys = _redis_cond_keys + (_redis_cond_offsets[cs] * 2);
        if (_klen > 0) {
            const short    *_lower = _keys;
            const short    *_mid;
            const short    *_upper = _keys + (_klen << 1) - 2;
            while (1) {
                if (_upper < _lower)
                    break;

                _mid = _lower + (((_upper - _lower) >> 1) & ~1);
                if (_widec < _mid[0])
                    _upper = _mid - 2;
                else if (_widec > _mid[1])
                    _lower = _mid + 2;
                else {
                    switch (_redis_cond_spaces[_redis_cond_offsets[cs] + ((_mid - _keys) >> 1)]) {
                    case 0:{
                            _widec = (short)(640 + ((*p) - -128));
                            if (
#line 79 "redis.rl"
                                   c_arg < argc)
                                _widec += 256;
                            break;
                        }
                    case 1:{
                            _widec = (short)(128 + ((*p) - -128));
                            if (
#line 82 "redis.rl"
                                   arglen-- > 0)
                                _widec += 256;
                            break;
                        }
                    case 2:{
                            _widec = (short)(1152 + ((*p) - -128));
                            if (
#line 79 "redis.rl"
                                   c_arg < argc)
                                _widec += 256;
                            if (
#line 82 "redis.rl"
                                   arglen-- > 0)
                                _widec += 512;
                            break;
                        }
                    }
                    break;
                }
            }
        }

        _keys = _redis_trans_keys + _redis_key_offsets[cs];
        _trans = _redis_index_offsets[cs];

        _klen = _redis_single_lengths[cs];
        if (_klen > 0) {
            const short    *_lower = _keys;
            const short    *_mid;
            const short    *_upper = _keys + _klen - 1;
            while (1) {
                if (_upper < _lower)
                    break;

                _mid = _lower + ((_upper - _lower) >> 1);
                if (_widec < *_mid)
                    _upper = _mid - 1;
                else if (_widec > *_mid)
                    _lower = _mid + 1;
                else {
                    _trans += (unsigned int)(_mid - _keys);
                    goto _match;
                }
            }
            _keys += _klen;
            _trans += _klen;
        }

        _klen = _redis_range_lengths[cs];
        if (_klen > 0) {
            const short    *_lower = _keys;
            const short    *_mid;
            const short    *_upper = _keys + (_klen << 1) - 2;
            while (1) {
                if (_upper < _lower)
                    break;

                _mid = _lower + (((_upper - _lower) >> 1) & ~1);
                if (_widec < _mid[0])
                    _upper = _mid - 2;
                else if (_widec > _mid[1])
                    _lower = _mid + 2;
                else {
                    _trans += (unsigned int)((_mid - _keys) >> 1);
                    goto _match;
                }
            }
            _trans += _klen;
        }

      _match:
        cs = _redis_trans_targs[_trans];

        if (_redis_trans_actions[_trans] == 0)
            goto _again;

        _acts = _redis_actions + _redis_trans_actions[_trans];
        _nacts = (unsigned int)*_acts++;
        while (_nacts-- > 0) {
            switch (*_acts++) {
            case 0:
#line 46 "redis.rl"
                {
                }
                break;
            case 2:
#line 51 "redis.rl"
                {
                    last = p;
                }
                break;
            case 3:
#line 54 "redis.rl"
                {
                    argc = atol(last);
                    msg = msg_new(argc);
                }
                break;
            case 4:
#line 59 "redis.rl"
                {
                    last = p;
                }
                break;
            case 5:
#line 62 "redis.rl"
                {
                    arglen = atol(last);
                    msg->argv[c_arg] = sdsnewlen(NULL, arglen);
                }
                break;
            case 6:
#line 67 "redis.rl"
                {
                    last = p;
                }
                break;
            case 7:
#line 70 "redis.rl"
                {
                    memcpy(msg->argv[c_arg], last, p - last);
                    len = p - last;
                    msg->argv[c_arg][len] = '\0';

                    c_arg++;
                }
                break;
#line 321 "redis.c"
            }
        }

      _again:
        if (cs == 0)
            goto _out;
        if (++p != pe)
            goto _resume;
      _test_eof:{
        }
        if (p == eof) {
            const char     *__acts = _redis_actions + _redis_eof_actions[cs];
            unsigned int    __nacts = (unsigned int)*__acts++;
            while (__nacts-- > 0) {
                switch (*__acts++) {
                case 1:
#line 48 "redis.rl"
                    {
                    }
                    break;
#line 342 "redis.c"
                }
            }
        }

      _out:{
        }
    }

#line 120 "redis.rl"

    return msg;
}

int
main()
{
    uint8_t         buf[] = "*3<>$3<>SET<>$5<>mykey<>$7<>myva<>e<>$5<>mykey<>";
    uint32_t        buflen = strlen(buf);
    int             i;
    Msg            *msg = msg_parse(buf, buflen);

    if (msg == NULL) {
        printf("error on parse msg");
    }
    printf("msg->argc: %d\n", msg->argc);
    for (i = 0; i < msg->argc; i++) {
        printf("%s\n", msg->argv[i]);
    }
}
