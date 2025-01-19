The following notes come from the YouTube playlist: [Introduction to Rasa](https://www.youtube.com/watch?v=Ap62n_YAVZ8&list=PL75e0qA87dlErcimrWHKEUq4b-x9PrpLe)
### Introduction to Rasa

Rasa is designed to help a task oriented dialogue system. This means the user wants to do something specific through talking to an automated system in a two-way conversation. **Task Oriented Dialogue System**.

Rasa is **a framework that makes it easier to build custom chatbots.**
The core of building a Rasa assistant is providing examples that your system can learn from. 

Rasa combines the history of NLP such as rule-based text and transformer-based text (neural methods).

#### Key Points:
- NLU (Natural Language Understanding): Raw text in, machine-readable information out
- Methods to do NLU:
	- Rule-based approach: cannot handle things it has not seen before
	- Neural approach: requires training examples (makes _informed guesses_)
- A Rasa assistant can use both methods.
- Dialog Policy: Given the conversation so far, what should your assistant say/do?
	- Rule-based Policy: A dialog tree of all possible paths a conversation can take. It cannot handle actual conversations with digressions and other inputs.
	- Neural Policy: This allows for a more natural conversation.
- It is recommended to use both policies.
- How do conversations work and improve over time? "Conversation-driven development" or manually reviewing and annotating conversations.

### Creating a New Assistant

Rasa is installed through pip and initialized in the command line interpreter (CLI). It already has a basic initial model easily initialized and ran. 

#### Key Points:
- Minimum files needed:
	- Domain file: shows everything the assistant knows about.
	- Config file: sets out our NLU pipeline.
	- At least 1 data file: by default, there are 3 data files: stories, rules, NLU.
		- NLU: different examples of how people can describe intent
		- Stories: potential conversation flow
		- Rules: to find conditional rules.

```python
1. rasa -h 
2. rasa train # trains a new model and stores it in the model directory
3. rasa shell # allows you to talk to the assistant inside the shell
4. rasa shell --debug # provides more information to be able to debug
```