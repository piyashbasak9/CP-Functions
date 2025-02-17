// Function to merge overlapping intervals in a sorted list
vector<pair<long long, long long>> mergeIntervals(vector<pair<long long, long long>> &intervals)
{
    if (intervals.empty()) // If the input list is empty, return an empty list
        return {};

    sort(intervals.begin(), intervals.end()); // Sort the intervals based on their start points
    vector<pair<long long, long long>> result;
    result.push_back(intervals[0]); // Start with the first interval

    // Iterate through intervals and merge overlapping ones
    for (size_t i = 1; i < intervals.size(); i++)
    {
        auto &last = result.back(); // Get the last interval in the result
        if (intervals[i].first <= last.second + 1) // Check for overlap
        {
            last.second = max(last.second, intervals[i].second); // Merge intervals
        }
        else
        {
            result.push_back(intervals[i]); // Add non-overlapping interval
        }
    }
    return result;
}

// Function to find the intersection of two sets of intervals
vector<pair<long long, long long>> intervalIntersection(vector<pair<long long, long long>> &set1, vector<pair<long long, long long>> &set2)
{
    vector<pair<long long, long long>> result;
    int i = 0, j = 0;
    
    // Sort both sets of intervals before processing
    sort(set1.begin(), set1.end());
    sort(set2.begin(), set2.end());

    // Use two-pointer technique to find overlapping intervals
    while (i < set1.size() && j < set2.size())
    {
        long long start = max(set1[i].first, set2[j].first); // Start of the intersection
        long long end = min(set1[i].second, set2[j].second); // End of the intersection

        if (start <= end) // If there is an actual intersection
        {
            result.push_back({start, end});
        }

        // Move the pointer that has the smaller endpoint
        if (set1[i].second < set2[j].second)
            i++;
        else
            j++;
    }
    return result;
}

// Function to generate a valid range between two numbers based on bitwise operations
vector<pair<long long, long long>> valid_range(long long prev, long long curr)
{
    vector<pair<long long, long long>> result;
    long long value = 0;

    // Iterate through bits from most significant (29th bit) to least significant (0th bit)
    for (int i = 29; i >= 0; i--)
    {
        long long currb = (curr & (1LL << i)) ? 1 : 0; // Get the i-th bit of curr
        long long prevb = (prev & (1LL << i)) ? 1 : 0; // Get the i-th bit of prev

        if (currb) // If the current bit is 1
        {
            value |= (1 - prevb) * (1LL << i); // Set bit conditionally
        }
        else
        {
            long long lb = value | ((1 - prevb) * (1LL << i)); // Calculate lower bound
            long long rb = lb;
            for (int j = i - 1; j >= 0; j--)
            {
                rb |= (1LL << j); // Set remaining bits to 1 for upper bound
            }
            result.push_back({lb, rb}); // Store the range
            value |= (prevb * (1LL << i)); // Update value based on prev bit
        }
    }
    result.push_back({value, value}); // Add final range
    return result;
}

// Function to check if a number is present in a given list of sorted intervals
bool isPresentInIntervals(const vector<pair<long long, long long>> &intervals, long long x)
{
    int left = 0, right = intervals.size() - 1;

    // Perform binary search for efficient lookup
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (intervals[mid].first <= x && x <= intervals[mid].second) // If x lies within an interval
        {
            return true;
        }
        else if (intervals[mid].second < x) // If x is greater, move right
        {
            left = mid + 1;
        }
        else // If x is smaller, move left
        {
            right = mid - 1;
        }
    }
    return false; // x not found in any interval
}

// Function to check if a value 'x' exists in a specific list of intervals at depth 'd'
bool check(long long d, long long x, const vector<vector<pair<long long, long long>>> &possible)
{
    return isPresentInIntervals(possible[d], x); // Check if x is within the intervals at depth d
}
