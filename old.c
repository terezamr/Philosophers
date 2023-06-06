int	get_time2(t_data *data)
{
	struct timeval	newtime;
	long			time;

	if (gettimeofday(&newtime, NULL) != 0)
	{
		perror("gettimeofday");
		return (1);
	}
	time = (newtime.tv_sec - data->time.tv_sec) * 1000
		+ (newtime.tv_usec - data->time.tv_usec) / 1000;
	return (time);
}