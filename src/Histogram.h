#include<math.h>
#include <limits>
#include <iostream>
#include <string>
using namespace std;
// A histogram class.
// The Histogram object can keep a tally of values
// within a range, the range is arranged into some
// number of bins specified during construction.
// Any allocation of a Histogram object may throw
// a bad_alloc exception.
class Histogram
{
private:
	double Start,nBins_by_interval;
	unsigned int nBins;
	unsigned int number;
	unsigned int* freq;
	double minValue, maxValue, mean, deviation, total;

public:
	// Construct a histogram that can count
	// within a range of values.
	// All bins of the histogram are set to zero.
	Histogram(
			  const double& Start,
			  const double& End,
			  const unsigned int& nBins):
	Start(Start),
	nBins_by_interval(nBins/(End-Start)),
	nBins(nBins),
	freq( new unsigned int[nBins] )
	{
      	reset();
	}
	// Construct a histogram by copying another one.
	Histogram(const Histogram& other):
		Start(other.Start),
		nBins_by_interval(other.nBins_by_interval),
		nBins(other.nBins),
		freq( new unsigned int[nBins] )
	{
		for(unsigned int i(0); i < nBins; ++i)
            freq[i] = other.freq[i];
	}
	
	void reset() {
		for(unsigned int i(0); i < nBins; ++i)
            freq[i] = 0U;
      	number=total=mean=deviation=0;
		minValue = std::numeric_limits<double>::max();
		maxValue = std::numeric_limits<double>::min();
		
	}
	
	// Deallocate the memory that was allocated for
	// the tallied counts.
	~Histogram() {delete[] freq;}
	// Set this histogram equal to another.
	Histogram& operator=(const Histogram& other)
	{
		if( this != &other )
		{
            Start = other.Start;
            nBins_by_interval = other.nBins_by_interval;
            if( nBins != other.nBins )
            {
				nBins = other.nBins;
				delete[] freq;
				freq = new unsigned int[nBins];
            }
            for(unsigned int i(0); i < nBins; ++i)
				freq[i] = other.freq[i];
		}
		return *this;
	}
	
	void Add(const double& x, int ntimes) {
		number+=ntimes;
		total+=(x*ntimes);
		mean+=(x*ntimes);
		deviation+= (x * x)*ntimes;
		minValue = min(minValue, x);
		maxValue = max(maxValue, x);
		
		const unsigned int i( static_cast<unsigned int>( (x-Start)*nBins_by_interval) );
		
		if( i < nBins ) {
			freq[i]+=ntimes;
		}
	}
	
	// Increase the count for the bin that holds a
	// value that is in range for this histogram.
	void Add(const double& x)
	{
		Add(x,1);
	}
	
	void end() {
		mean = mean / number;
		deviation = deviation/number - mean * mean;
		deviation = sqrt(deviation);
	}
	
	void dumpStr(ostream &outfile) {
		int maxfreq=0;
		for(unsigned int i=0; i<nBins && i<=maxValue;i++) {
			outfile << i << "  " << freq[i] << endl;
			maxfreq = freq[i]>maxfreq ? freq[i] : maxfreq;
		}
		
		outfile << "# Number: "<<number <<endl;
		outfile << "# Mean: "<<mean<<endl;
		outfile << "# Deviation: "<<deviation<<endl;
		outfile << "# Min: "<<minValue<<endl;
		outfile << "# Max: "<<maxValue<<endl;

		unsigned int max=15;
		for(unsigned int i=maxValue<nBins?maxValue:nBins; i>15; i--) {
			if(freq[i]>maxfreq/10000) {
				max = i;
				break;
			}
		}
		outfile << "# Latest: "<<max<<endl;
	}
	
	void dump(const char * name, const char *suffix) {
		string fileName(name);
		fileName.append(suffix);
		ofstream outfile;
		
		cout << "Writing histogram to: " << fileName << endl;
			
		outfile.open(fileName.c_str());

		dumpStr(outfile);
		
		outfile.close();
	}
	
	// Get the sum of all counts in the histogram.
	const unsigned int GetTotalCount() const
	{
		unsigned int c(0U);
		for( unsigned int i(0); i < nBins; ++i )
            c += freq[i];
		return c;
	}
};
