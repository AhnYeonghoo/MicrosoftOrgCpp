

void func(void *data, int length)
{
    char *c = (char *)(data);
    for (int i = 0; i < length; i++)
    {
        *c = 0x41;
        ++c;
    }
}