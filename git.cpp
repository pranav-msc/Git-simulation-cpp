#include <bits/stdc++.h>
using namespace std;

class Commit
{
private:
    string message;
    vector<string> filesInCommit; //holds files related to a commit
public:
    //constructor
    Commit(string);
    string getMessage();
    void pushFilesCommitted(vector<string> &);
};

class Branch
{
private:
    //vector holds commits of respectively branches
    vector<Commit> commits;
    string branchName;

public:
    //constructor
    Branch(string);
    void addCommit(vector<string> &);
    //void addCommit2(vector<Commit> & v);
    string getName();
    void printCommits();
    vector<Commit> &getCommits();
};

//A Git repo represents a project
class Project
{
protected:
    //vector holds different branches in the project
    vector<Branch> branches;

    string curr_branch;

public:
    //default constructor
    Project()
    {
    }
    //to print the log of commits
    void log();
    //shift to new branch
    void checkout(string branch_name);
    //creates a new branch
    void checkout_b(string branch_name);
    //makes master branch(if not)
    void makeMasterBranch();
    Branch getBranch();
    void merge(string branch_name);
    vector<Branch> &getBranches();
    string getCurrBranch();
    //copy constructor
    Project(Project &);
    //overloading insertion operator to simulate git log(using friend function)
    friend ostream &operator<<(ostream &dout, Project &p);
    //destructor
    ~Project();
};

//Directory class holds files(represented by strings)
class Directory
{
protected:
    //files in directory
    vector<string> files; // A name identifies a unique file
public:
    //default constructor
    Directory()
    {
    }
    void addFile(string name);
    void listFiles();
    bool isEmpty();
    vector<string> &getFiles();
    //copy constructor
    Directory(Directory &);
};

//Represents staging area used to track non-commited files
class StagingArea : public Directory
{
protected:
    //files in staging area
    vector<bool> track; //boolean vector signifies which file is being tracked
public:
    //default constructor
    StagingArea()
    {
    }

    void viewTrackedFiles(Directory &);
    void viewUntrackedFiles(Directory &);
    void addFilesToStagingArea(string, Directory &);
    void copyToTrack(Directory &);
    vector<bool> &getTrack();
    //copy constructor
    StagingArea(StagingArea &);
};

class Repository : public StagingArea, public Project
{
private:
    //files already committed
    vector<bool> committed; //boolean vector signifies which file is being committed
public:
    //default constructor
    Repository()
    {
    }
    void viewFilesInRepos(Directory &);
    void addFilesToCommit(Directory &, Project &, StagingArea &);
    Repository &copyStagingToRepo(Directory &);
    //copy constructor
    Repository(Repository &);
};
