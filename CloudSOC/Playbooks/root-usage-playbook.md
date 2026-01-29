# pending
# Root User Activity Playbook

## 1. Alert Overview
- **Severity:** Critical
- **Category:** Exploitation
- **Data Source:** AWS CloudTrail
- **Trigger Condition:** Root account usage has been detected

## 2. Why This Alert Matters
Root account usage could indicate the highest level of compromise and potential damage.

## 3. Initial Triage (First 5 Minutes)
- Identify any related alerts (IAM Escalation, Login Attempts)
- Confirm source IP address and region
- Determine whether the usage is scheduled (i.e. billing) or unscheduled
- Check what actions have been taken by the user

## 4. Investigation Steps
### Review the triggering event
```sql
fields @timestamp, eventName, errorCode, userIdentity.userName, sourceIPAddress, userAgent
| filter eventName="identityType = Root"
| sort @timestamp desc
```
## 5. False Positive Analysis

Possible benign causes:
- scheduled usage

Validate:
- confirm unscheduled usage
- Review Actions taken
- Check any correlating alerts

## 6. Containment Actions
- Restrict IAM permissions temporarily
- Disable keys if external IP
- Force password reset if suspected compromise

## 7. Eradication & Recovery
- Rotate credentials
- Review IAM for least privilege
- Force password reset if suspected compromise

## 8. Post-Incident Improvements
- Correlate with IAM enumeration alerts
- Tune threshold based on environment baseline
