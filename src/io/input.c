#include "io/input.h"
#include <stdio.h>
#include <stdlib.h>
#include "core/smoinfo.h"
#include "def/strutil.h"
#include "util/log.h"


static bool ParseInputCmd(const char* cmd, struct SmoInfo* smo);


bool InputParseFile(const char* fname, struct SmoInfo* smo)
{
    bool res = false;

    FILE* f = NULL;
    if(fopen_s(&f, fname, "r"))
    {
        LogPrintE("Cannot open file '%s'.", fname);
        return false;
    }

    char buf[255];
    while(fgets(buf, 255, f))
    {
        if(StrIsNullOrSpace(buf))
            continue;

        buf[strlen(buf)-1] = '\0';              // to ignore '\n\0'
        if(!ParseInputCmd(buf, smo))
            goto lbl_cleanup;
    }

    res = true;

lbl_cleanup:
    fclose(f);

    return res;
}


static bool ParseInputCmd(const char* cmd, struct SmoInfo* smo)
{
    bool res = false;
    const uint cmd_len = strlen(cmd);
    uint num_tok = 0;
    char* tok_lst[32];
    char* ctx, *tok;
    char* num_conv_end;

// split the command
    char* buf = malloc(cmd_len + 1);
    memcpy_s(buf, cmd_len+1, cmd, cmd_len);
    buf[cmd_len] = '\0';
    StrToLower(buf);

    char* it_comment = strchr(buf, ';');
    if(it_comment)
    {
        *it_comment = '\0';
        if(StrIsNullOrSpace(buf))
        { res = true; goto lbl_cleanup; }
    }

    tok = strtok_s(buf, "\t =,", &ctx);
    for(; tok; ++num_tok)
    {
        tok_lst[num_tok] = tok;
        tok = strtok_s(NULL, "\t =,", &ctx);
    }

// now parse the command
    if(1 <= num_tok && strchr(";[", tok_lst[0][0]))                                    // comment or section (like in .ini files)
    {
        res = true;
        goto lbl_cleanup;
    }
    if(num_tok < 2)
    {
        LogPrintE("Invalid syntax for input line '%s'.", cmd);
        goto lbl_cleanup;
    }

    if(StrStartsWith(tok_lst[0], PARAM_ARRIVAL_RATE))
    {
        smo->ArrivalRate = strtod(tok_lst[1], &num_conv_end);
        if(tok_lst[1] == num_conv_end)
        {
            LogPrintE("Cannot parse number value in the command '%s'.", cmd);
            goto lbl_cleanup;
        }
    }
    else
    if(StrStartsWith(tok_lst[0], PARAM_DEPARTURE_RATE))
    {
        smo->DepartureRate = strtod(tok_lst[1], &num_conv_end);
        if(tok_lst[1] == num_conv_end)
        {
            LogPrintE("Cannot parse number value in the command '%s'.", cmd);
            goto lbl_cleanup;
        }
    }
    else
    if(StrStartsWith(tok_lst[0], PARAM_LEAVING_RATE))
    {
        smo->LeavingRate = strtod(tok_lst[1], &num_conv_end);
        if(tok_lst[1] == num_conv_end)
        {
            LogPrintE("Cannot parse number value in the command '%s'.", cmd);
            goto lbl_cleanup;
        }
    }
    else
    if(StrStartsWith(tok_lst[0], PARAM_CHANNEL_NUM))
    {
        smo->ChannelNum = strtoul(tok_lst[1], &num_conv_end, 10);
        if(tok_lst[1] == num_conv_end)
        {
            LogPrintE("Cannot parse number value in the command '%s'.", cmd);
            goto lbl_cleanup;
        }
    }
    else
    if(StrStartsWith(tok_lst[0], PARAM_QUEUE_LEN))
    {
        smo->QueueLen = strtoul(tok_lst[1], &num_conv_end, 10);
        if(tok_lst[1] == num_conv_end)
        {
            LogPrintE("Cannot parse number value in the command '%s'.", cmd);
            goto lbl_cleanup;
        }
    }
    else
    if(StrStartsWith(tok_lst[0], PARAM_TIME_START))
    {
        smo->SimTimeBeg = strtod(tok_lst[1], &num_conv_end);
        if(tok_lst[1] == num_conv_end)
        {
            LogPrintE("Cannot parse number value in the command '%s'.", cmd);
            goto lbl_cleanup;
        }
    }
    else
    if(StrStartsWith(tok_lst[0], PARAM_TIME_END))
    {
        smo->SimTimeEnd = strtod(tok_lst[1], &num_conv_end);
        if(tok_lst[1] == num_conv_end)
        {
            LogPrintE("Cannot parse number value in the command '%s'.", cmd);
            goto lbl_cleanup;
        }
    }
    else
    if(StrStartsWith(tok_lst[0], PARAM_NUM_STEP))
    {
        smo->SimNumStep = strtoul(tok_lst[1], &num_conv_end, 10);
        if(tok_lst[1] == num_conv_end)
        {
            LogPrintE("Cannot parse number value in the command '%s'.", cmd);
            goto lbl_cleanup;
        }
    }
    else
    {
        LogPrintE("Unknown input command '%s'.", cmd);
        goto lbl_cleanup;
    }

    res = true;

lbl_cleanup:
    free(buf);

    return res;
}
