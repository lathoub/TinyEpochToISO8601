char dateTime [sizeof "2021-04-18T10:09:34Z"];

char *toDateTime(const unsigned long epoch)
{
  uint32_t a;
  uint32_t b;
  uint32_t c;
  uint32_t d;
  uint32_t e;
  uint32_t f;

  unsigned long t = epoch;

  //Negative Unix time values are not supported
  if (t < 1)
    t = 0;

  //Retrieve hours, minutes and seconds
  auto seconds = t % 60;
  t /= 60;
  auto minutes = t % 60;
  t /= 60;
  auto hours = t % 24;
  t /= 24;

  //Convert Unix time to date
  a = (uint32_t)((4 * t + 102032) / 146097 + 15);
  b = (uint32_t)(t + 2442113 + a - (a / 4));
  c = (20 * b - 2442) / 7305;
  d = b - 365 * c - (c / 4);
  e = d * 1000 / 30601;
  f = d - e * 30 - e * 601 / 1000;

  //January and February are counted as months 13 and 14 of the previous year
  if (e <= 13)
  {
    c -= 4716;
    e -= 1;
  }
  else
  {
    c -= 4715;
    e -= 13;
  }

  //Retrieve year, month and day
  auto year = c;
  auto month = e;
  auto day = f;

  sprintf(dateTime, "%4d-%02d-%02dT%02d:%02d:%02d", year, month, day, hours, minutes, seconds);

  return dateTime;
}