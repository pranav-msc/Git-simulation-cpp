#include "git.cpp"
using namespace std;
Commit::Commit(string message)
{
    this->message = message;
}

string Commit::getMessage()
{
    return message;
}

void Commit::pushFilesCommitted(vector<string> &filesCommited)
{
    for (int i = 0; i < filesCommited.size(); i++)
    {
        filesInCommit.push_back(filesCommited[i]);
    }
}

vector<Commit> &Branch::getCommits()
{
    return commits;
}
Branch::Branch(string branchName)
{
    this->branchName = branchName;
}

void Branch::addCommit(vector<string> &filesCommited)
{
    cout << "\nEnter commit message: ";
    string message;
    getline(cin, message);
    Commit commit(message);
    commit.pushFilesCommitted(filesCommited);
    commits.push_back(commit);
}

string Branch::getName()
{
    return branchName;
}

void Branch::printCommits()
{
    for (int i = 0; i < commits.size(); i++)
    {
        cout << commits[i].getMessage() << endl;
    }
}

void Project::log()
{
    for (int i = 0; i < branches.size(); i++)
    {
        cout << "Commits in branch " << branches[i].getName() << " :\n";
        branches[i].printCommits();
        cout << endl;
    }
}
//friend function(of project class)
ostream &operator<<(ostream &dout, Project &p)
{
    p.log();
    return dout;
}

void Project::makeMasterBranch()
{
    if (branches.size() == 0)
    {
        Branch b1("master");
        branches.push_back(b1);
        curr_branch = "master";
    }
}

Branch Project ::getBranch()
{
    cout << "Your current working branch is " << curr_branch << endl;
    int i;
    for (i = 0; i < branches.size(); i++)
    {
        if (branches[i].getName() == curr_branch)
        {
            return branches[i];
        }
    }
    return branches[i - 1];
}
string Project::getCurrBranch()
{
    return curr_branch;
}

void Project ::checkout(string branch_name)
{
    int i;
    for (i = 0; i < branches.size(); i++)
    {
        if (branches[i].getName() == branch_name)
        {
            curr_branch = branch_name;
            cout << "\nShifted to " << curr_branch;
            break;
        }
    }
    if (i == branches.size())
    {
        cout << "\n"
             << branch_name << " does not exist";
    }
}

void Project::checkout_b(string branch_name)
{
    int i;
    for (i = 0; i < branches.size(); i++)
    {
        if (branches[i].getName() == branch_name)
        {

            return;
        }
    }
    //Branch b1(branch_name);
    Branch *b1 = new Branch(branch_name);
    branches.push_back(*b1);
    cout << "\nCreated a new branch " << branch_name << " and shifted.";
    curr_branch = branch_name;
}

vector<Branch> &Project ::getBranches()
{
    return branches;
}
Project ::~Project()
{
}

void Directory::addFile(string fileName)
{
    files.push_back(fileName);
}

void Directory::listFiles()
{
    cout << "\nFiles in the repository:\n";
    for (int i = 0; i < files.size(); i++)
    {
        cout << "\t"
             << files[i];
    }
}

bool Directory ::isEmpty()
{
    if (files.size() == 0)
        return true;
    return false;
}
vector<string> &Directory ::getFiles()
{
    return files;
}

void StagingArea::copyToTrack(Directory &d)
{
    vector<string> s = d.getFiles();
    int i;
    for (int i = 0; i < s.size(); i++)
    {
        track.push_back(false);
    }
}

vector<bool> &StagingArea ::getTrack()
{
    return track;
}

void StagingArea::viewTrackedFiles(Directory &d)
{
    vector<string> s = d.getFiles();
    int i;
    cout << "\nFollowing files added to staging area:";
    for (i = 0; i < track.size(); i++)
    {
        if (track[i])
        {
            cout << "\n"
                 << s[i];
        }
    }
}
void StagingArea::viewUntrackedFiles(Directory &d)
{
    vector<string> s = d.getFiles();
    int i;
    cout << "\nFollowing files not added to staging area:";
    for (i = 0; i < track.size(); i++)
    {
        if (!track[i])
        {
            cout << "\n"
                 << s[i];
        }
    }
}

void StagingArea ::addFilesToStagingArea(string file_name, Directory &d)
{
    //cout<<d.files.size();
    vector<string> s = d.getFiles();
    int i;
    if (track.size() == 0)
    {
        copyToTrack(d);
    }
    for (i = 0; i < s.size(); i++)
    {

        if (s[i] == file_name)
        {

            track[i] = true;
            cout << "\nFile successfully added to the staging area";
            return;
        }
    }

    if (i == s.size())
    {
        cout << "\nGiven file does not exists";
    }
}

Repository &Repository::copyStagingToRepo(Directory &d)
{
    vector<string> files = d.getFiles();
    if (committed.size() == 0)
    {
        for (int i = 0; i < files.size(); i++)
        {
            committed.push_back(false);
        }
    }
    return *this;
}
void Repository::viewFilesInRepos(Directory &d)

{
    vector<string> files = d.getFiles();
    int i;
    cout << "\nFollowing files are present in the repository:";
    for (i = 0; i < committed.size(); i++)
    {
        if (committed[i])
        {
            cout << "\n"
                 << files[i];
        }
    }
}

void Repository ::addFilesToCommit(Directory &d, Project &p, StagingArea &t)
{
    vector<string> files = d.getFiles();
    int i;
    vector<bool> &track = t.getTrack();
    p.makeMasterBranch();
    vector<Branch> &branches = p.getBranches();

    for (i = 0; i < track.size(); i++)
    {
        committed[i] = track[i];
    }
    vector<string> filesCommited;
    for (i = 0; i < files.size(); i++)
    {

        if (committed[i])
        {
            filesCommited.push_back(files[i]);
        }
    }

    for (i = 0; i < branches.size(); i++)
    {

        if (branches[i].getName() == p.getCurrBranch())
        {

            branches[i].addCommit(filesCommited);
            break;
        }
    }
    if (i == branches.size())
    {
        cout << "\nThe given branch does not exists";
    }
}
//All copy constructors
/*Commit ::Commit(Commit& c){
message=c.message;
filesInCommit=c.filesInCommit;
}
Branch ::Branch(Branch& c){
commits=c.commits;
branchName=c.branchName;
}*/
Project ::Project(Project &c)
{
    cout << "Cloned repo" << endl;
    branches = c.branches;
    curr_branch = c.curr_branch;
}
Repository::Repository(Repository &c)
{
    committed = c.committed;
}
Directory::Directory(Directory &c)
{
    files = c.files;
}
StagingArea::StagingArea(StagingArea &c)
{
    track = c.track;
}