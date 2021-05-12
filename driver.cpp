#include "git_methods.cpp"
int main()
{
    int flag = 0;
    cout << "\nCommands menu: "
         << "\n1. git init"
         << "\n2. git add"
         << "\n3. git status"
         << "\n4. git commit -m "
         << "\n5.git branch"
         << "\n6.git checkout -b <branch_name>"
         << "\n7. git log"
         << "\n8. git checkout <branch_name>"
         << "\n9. touch"
         << "\n10. viewFilesInRepo"
         << "\n11. exit"
         << endl;

    char p = 'y';
    string command;
    Project project;
    StagingArea stagingArea;
    Directory directory;
    Repository repository;
    while (p == 'y')
    {

        cout << "\nEnter a command: ";
        getline(cin, command);
        if (command == "git init")
        {
            flag = 1;
            cout << "\nEmpty project has been initialised";
            continue;
        }
        if (flag)
        {
            if (command == "git add")
            {

                if (directory.isEmpty())
                {
                    cout << "\nAdd some files to your Directory!";
                    cout << "\nEnter how many files to add: ";
                    int t;
                    cin >> t;
                    for (int i = 0; i < t; i++)
                    {
                        string fileName;
                        cout << "\nEnter file name: ";
                        cin >> fileName;
                        directory.addFile(fileName);
                    }
                }
                else
                {
                    int temp = 1;
                    while (temp == 1)
                    {
                        cout << "\nEnter file to be added to the staging area: ";
                        string fileName;
                        cin >> fileName;
                        stagingArea.addFilesToStagingArea(fileName, directory);
                        cout << "\nEnter 1 to add more files to staging area?";
                        cin >> temp;
                    }
                }
                getchar();
            }
            else if (command == "git status")
            {
                stagingArea.viewTrackedFiles(directory);
                stagingArea.viewUntrackedFiles(directory);
            }
            else if (command == "git branch")
            {
                cout << "\nYour current branch is: "
                     << project.getCurrBranch();
            }

            else if (command == "git log")
            {
                //project.log();
                cout << project;
            }
            else if (command.substr(0, 15) == "git checkout -b")
            {

                string branchName = command.substr(16, command.size() - 1);
                project.checkout_b(branchName);
            }
            else if (command.substr(0, 12) == "git checkout")
            {
                string branchName = command.substr(13, command.size() - 1);
                project.checkout(branchName);
            }

            else if (command == "git commit -m")
            {
                repository.copyStagingToRepo(directory).addFilesToCommit(directory, project, stagingArea);
            }
            else if (command == "touch")
            {

                cout << "\nEnter how many files to add in directory: ";
                int t;
                cin >> t;
                for (int i = 0; i < t; i++)
                {
                    string fileName;
                    cout << "\nEnter file name: ";
                    cin >> fileName;
                    directory.addFile(fileName);
                    stagingArea.copyToTrack(directory);
                }
                getchar();
            }
            else if (command == "viewFilesInRepo")
            {
                repository.viewFilesInRepos(directory);
            }
            else if (command == "exit")
            {
                break;
            }
            else
            {
                cout << "\nInvalid command";
            }
        }
        else
        {
            cout << "\nPlease initialize your project";
        }

        //getchar();
    }
    //git clone
    Project project2 = project;
    StagingArea stagingArea2 = stagingArea;
    Directory directory2 = directory;
    Repository repository2 = repository;
    project2.log();
    stagingArea2.viewTrackedFiles(directory2);
    cout << endl;
    return 0;
}
