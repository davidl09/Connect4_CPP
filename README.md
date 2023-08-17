# Connect4_CPP
<h4>
  Implementing the MiniMax search algorithm to make an "unbeatable" connect-4 agent. Pull from 'master' branch to get stable CLI interface. Current working branch is 'improved-1.2'. 
</h4>


<h3>
  HOW TO BUILD: (Linux)
</h3>
<ol>
  <li>
    $ git clone https://github.com/davidl09/Connect4_CPP connect-4
  </li>
  <li>
    $ cd connect-4
  </li>
  <li>
    $ mkdir build && cd build
  </li>
  <li>
    $ cmake ..
  </li>
  <li>
    $ make
  </li>
  <li>
    $ ./connect-4 ${SEARCH_DEPTH}
  </li>
</ol>
<p>
  ${SEARCH_DEPTH} is an optional parameter specifying how many 'plys' i.e. turns the algorithm should consider. Some considerations:
  <ul>
    <li>
      Any value below 3 may result in odd behaviour or bugs
    </li>
    <li>
      Any value above 13-14 will make the game unplayable, due to exponentially bounded complexity of this algorithm (Worst case <b>O(7<sup>n</sup>)!!</b>)
    </li>
    <li>
      The agent uses alpha-beta pruning and optimized search ordering, which causes it to start playing significantly faster once a win solution has been found.
    </li>
  </ul>
</p>
<h4>
  OPTIONAL: (make this game accessible from anywhere on the command line)
</h4>
<ul>
  <li>
    sudo chmod +x connect-4
  </li>
  <li>
    sudo cp connect-4 /usr/local/bin/connect-4
  </li>
</ul>

