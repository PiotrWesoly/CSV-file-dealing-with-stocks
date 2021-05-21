#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <list>
#include <vector>

using namespace std;

string mostTraded(vector<string>, vector<long>);
string highestDiff(vector<string> name, vector<float> openingPrice, vector<float> closingPrice);
string stockGrowth(vector<string> names, vector<string> date,  vector<float> openingPrice, vector<float> closingPrice);
void highestPrice(vector<string> name,vector<string> date, vector<float> maxPrice);
void portfolioValuation(map<string, int> portfolio,vector<string> names, vector<string> date, vector<float> openingPrice,vector<float> closingPrice);
map<string, int> creatingPortfolio();


int main() {

    string fileName="stocks.csv";

    vector<string> name, date;
    vector<float> openingPrice, maxPrice, minPrice, closingPrice;
    vector<long> volume;
    string tempName,tempDate;
    //float tempOpeningPrice,tempMaxPrice,tempMinPrice,tempClosePrice,tempVol;
    string tempOpeningPrice,tempMaxPrice,tempMinPrice,tempClosePrice,tempVol;
    char comma=',';
    map<string, int> portfolio;

    ifstream ifs(fileName);
        if (ifs.fail()) {
            cout << "Could not load the file" << endl;
        }
        else{
            cout<<"File loaded successfully"<<endl;
        }

        while(!ifs.eof()){
//            ifs>>tempName>>comma>>tempDate>>comma>>tempOpeningPrice>>comma>>tempMaxPrice
//               >>tempMinPrice>>comma>>tempClosePrice>>comma>>tempVol>>comma;

            getline(ifs, tempName, ',');
            getline(ifs, tempDate, ',');
            getline(ifs, tempOpeningPrice, ',');
            getline(ifs, tempMaxPrice, ',');
            getline(ifs, tempMinPrice, ',');
            getline(ifs, tempClosePrice, ',');
            getline(ifs, tempVol);


            name.push_back(tempName);
            date.push_back(tempDate);
            openingPrice.push_back(stof(tempOpeningPrice));
            maxPrice.push_back(stof(tempMaxPrice));
            minPrice.push_back(stof(tempMinPrice));
            closingPrice.push_back(stof(tempClosePrice));
            volume.push_back(stol(tempVol));

        }

    ifs.close();

        portfolio = creatingPortfolio();

        cout<<"Most traded: "<<mostTraded(name, volume)<<endl
            <<"Highest daily appreciation: "<<highestDiff(name, openingPrice, closingPrice)<<endl
            <<"Highest stock growth: "<<stockGrowth(name,date, openingPrice, closingPrice )<<endl;
        highestPrice(name, date, maxPrice);
        portfolioValuation(portfolio, name, date, openingPrice, closingPrice);



        return 0;
}

string mostTraded(vector<string> name, vector<long> volume){

    map<string, long> data;
    string most_traded;
    long max=0;

    for(int  i=0; i<name.size(); i++){
       data[name.at(i)]+= volume.at(i);
    }
    for(auto const& [key, value] : data ){
        if(data[key]>max){
            max=data[key];
            most_traded=key;
        }
    }
    return most_traded;
}

string highestDiff(vector<string> name, vector<float> openingPrice, vector<float> closingPrice){

    float max=0;
    string highest;

    for(int i=0; i<name.size(); i++){
        if((closingPrice.at(i)-openingPrice.at(i))>max){
            max=(closingPrice.at(i)-openingPrice.at(i));
            highest=name.at(i);
        }
    }
    return highest;
}

string stockGrowth(vector <string> names,vector<string> date, vector <float> openingPrice, vector<float> closingPrice) {

    map<string, pair<float, float>> data;
    float max=0;
    string result;

    for (int i = 0; i < names.size(); i++) {
        if (date.at(i) == "02-Nov-2015") data[names.at(i)].first = openingPrice.at(i);
        if (date.at(i) == "25-Nov-2015") data[names.at(i)].second = closingPrice.at(i);
       // cout<<data[names.at(i)].first<<" "<<data[names.at(i)].second<<endl;
    }
//    for (const auto& [key, value] : data) {
//        cout <<setw(10)<<left<<key<<setw(15)<<left<<data[key].first<<setw(10)<<data[key].second<<endl;
//    }

    for(int i=0; i<data.size();i++){
        if((data[names.at(i)].second-data[names.at(i)].first)>max){
            max=(data[names.at(i)].second-data[names.at(i)].first);
            //cout<<max<<" ";
            result = names.at(i);
        }
    }
    return result;
}

void highestPrice(vector<string> name,vector<string> date, vector<float> maxPrice){

    map<string, pair<string, float>> data;
    float max=0.F;
    //vector<int> highestPriceIndex;

    for(int  i=0; i<maxPrice.size(); i++){
        if(data.find(name.at(i))==data.end()) max=0.F;
        if(maxPrice.at(i)>max){
            max=maxPrice.at(i);
            data[name.at(i)].first=date.at(i);
            data[name.at(i)].second=maxPrice.at(i);
        }
    }
    cout<<endl<<"Highest price :"<<endl;

    for (const auto& [key, value] : data) {
        cout <<setw(10)<<left<<key<<setw(15)<<left<<data[key].first<<setw(10)<<data[key].second<<endl;
    }
}

void portfolioValuation(map<string, int> portfolio,vector<string> names, vector<string> date, vector<float> openingPrice,vector<float> closingPrice){
    string startingDate, endDate;
    map<string, pair<float, float>> data;
    map<string, float> result;

    cout<<"Enter starting date form which you want to calculate value of your stocks (example: 20-Nov-2015)"<<endl
        <<"The range is 02-Nov-2015 to 25-Nov-2015: ";
    cin>>startingDate;
    cout<<endl<<"Enter end date: ";
    cin>>endDate;
//    startingDate="02-Nov-2015";
//    endDate="10-Nov-2015";

    for (int i = 0; i < names.size(); i++) {
        if (date.at(i) == startingDate) data[names.at(i)].first = openingPrice.at(i);
        if (date.at(i) == endDate) data[names.at(i)].second = closingPrice.at(i);
    }
    for (const auto& [key, value] : data) {
        if((data[key].second-data[key].first)*portfolio[key]==0 or (data[key].second-data[key].first)*portfolio[key]==-0)continue;
        result[key]=(data[key].second-data[key].first)*portfolio[key];
    }

    for (const auto& [key, value] : result) {
        cout <<setw(10)<<left<<key<<setw(15)<<left<<result[key]<<endl;
    }
}

map<string, int> creatingPortfolio(){
    map<string, int> portfolio;
    portfolio["NFLX"]=100;
    portfolio["CSCO"]=80;
    portfolio["INTC"]=120;
    portfolio["QCOM"]=70;
    portfolio["ALU"]=90;
    portfolio["IBM"]=80;
    portfolio["ARMH"]=110;
    return portfolio;
}
