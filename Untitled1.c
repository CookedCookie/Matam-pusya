void mergesort(MergeElement a[])
{
    num = sizeof(a)/sizeof(*a);
    int rght, rend;
    int i, j, m;

    for (int k = 1; k < num; k *= 2)
    {
        for (int left = 0; left + k < num; left += k * 2)
        {
            rght = left + k;
            rend = rght + k;
            if (rend > num) rend = num;
            m = left; i = left; j = rght;
            while (i < rght && j < rend)
            {
                if (a[i] <= a[j])
                {
                    b[m] = a[i]; i++;
                }
                else
                {
                    b[m] = a[j]; j++;
                }
                m++;
            }
            while (i < rght)
            {
                b[m] = a[i];
                i++; m++;
            }
            while (j < rend)
            {
                b[m] = a[j];
                j++; m++;
            }
            for (m = left; m < rend; m++)
            {
                a[m] = b[m];
            }
        }
    }
}
