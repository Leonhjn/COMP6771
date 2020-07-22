#include "comp6771/word_ladder.hpp"
#include <queue>
#include <string>

// Write your implementation here

namespace word_ladder {
    auto generate(std::string const& from,
	                            std::string const& to,
	                            absl::flat_hash_set<std::string> const& lexicon)
	   -> std::vector<std::vector<std::string>>
	   {
            //Create a visited hash set
	   		absl::flat_hash_set<std::string> visited;
            //Create a result array (vector)
	   		std::vector<std::vector<std::string>> result;
            //Create a queue for BFS
	   		std::queue<std::vector<std::string>> q;
            //Load from to the queue
	   		std::vector<std::string> fr = {from};
	   		q.push(fr);
            //Start of BFS
            //std::queue<int> deep;
            //deep.push(1) ;
            //auto result_deep = 100000;
            while (!q.empty())
            {
                //pop an path from the queue
            	auto size = q.size();
                if (result.size() != 0){
                    return result;
                }
                for (unsigned k = 0; k < size; k++){
                    std::vector<std::string> current = q.front();
            	    //auto current_deep = deep.front();
            	    //if ( current_deep >= result_deep ) {
            		//    return result;
                 	//};
                	q.pop();
                	//deep.pop();
				    //mark the word (the last element of the path) as visited
            	    auto node = current.back();
            	    visited.insert(node);

                    for (unsigned i = 0; i < node.length(); i++)
                    {
					   for (char j='a'; j <= 'z' ; j++)
					   {
                        	node.at(i) = j;
                            if ((lexicon.count(node) != 0) && ((visited.count(node) == 0))) {
                                //new path = old path + made up word
                        	    current.push_back(node);

                                if ( node == to ) {
                                    result.push_back(current);
                                    //result_deep = current_deep + 1;
                                } else
                                {
                                    q.push(current);
                                    //deep.push(current_deep + 1);
                                }
                                current.pop_back();
                            }
                        }
                    }
                }
            return result;
			}
        }
} // namespace word_ladder