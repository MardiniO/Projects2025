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

### The Domain File (Intents & Responses)

The domain file is the most important file in Rasa. The domain file is a directory of everything that your assistant 'knows'.

#### Key Points:
- In the domain file, there are:
	- Responses: what the assistant will reply.
	- Intents: categories of things user can say that will warrant a response.
	- Slots: variables remembered over the course of the conversation.
	- Entities: pieces of information extracted from raw input text.
	- Forms and Actions: these add application logic and extend what the assistant can do.
- Assistant has rigid replies unless we have Natural Language Generation (NLG).
- Slots are e.g. {name}
- Responses can be button/images. They have to be specifically designed and formatted in CSS.
- Intents are what the users say to the assistant.
- **Pro-Tip:** Start with the fewest intents possible.

### Training Data and Rules

In the context of a Rasa project, there are multiple different types of data:
- Text data used to pretrain any models or features we are using
- User-generated text
- Patterns of conversation

#### Key Points
- Giving examples of where we can find data for training:
	- Customer support logs
	- User conversations with your assistant (__best choice__)
- Stories, rules, determine how conversations should go.
- Intents, determine how users say things.
- Default guidelines use the TED policy to guess what to reply if it does not follow the stories.
- If the reply does not meet a certain confidence threshold, reply with a fallback.
- If generating your own conversational patterns, (initially)
	- start with common flows, "happy paths"
	- add common errors/digressions
- In stories, there is a feature "**feedback**". 
- Rules describe short pieces of conversation that always go the same way.
- Intents are determined and saved in NLU file.
- Give users an escape hatch right away. (in and out of scope intent)
- Do not use intents for saving information, use _entities or slots_ instead.
- If the utterance(user text) is ambiguous, use end-to-end instead (the raw text as training data without classifying it)


**Important Points**
- Have small stories that aren't full conversations. They will be later combined.
- Use rules for one-off interactions. Do not use rules for multi-turn interactions.
- Do not use OR statements and checkpointing often
- Do not write out every possible conversation flow start to finish
- ASAP do user testing
- Use modified content analysis:
	- Go through data by hand and assign each data point to a group
	- If no existing group fits, add a new one.
	- At given intervals, go through your groups and combine or separate them as needed.
	- Start with 2-3 passes through your dataset.
